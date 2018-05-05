#include "neuralNetwork.h"

Layer::~Layer() {
}

Layer::Layer(std::ifstream &file, int inputSize, int outputSize, bool last)
: biais(outputSize), weights(outputSize, inputSize), lastLayer(last)
{
	for (int i = 0; i < outputSize; i++) {
		for (int j = 0; j < inputSize; j++) {
			file >> weights[i][j];
		}
	}
	for (int i = 0; i < outputSize; i++) {
		file >> biais[i];
	}
}

Vector Layer::forward(Vector &input, std::stack<Vector> *outputsStack) {
	Vector result = weights * input + biais;
	if (outputsStack && !lastLayer)
		outputsStack->push(result);
	if (lastLayer)
		return result.softmax();
	return result.relu();
}

NeuralNetwork::~NeuralNetwork() {
	for (auto it = layers.begin(); it !=  layers.end(); ++ it) {
		delete *it;
	}
}

NeuralNetwork::NeuralNetwork() {
	std::ifstream file(PARAM_FILE);
	if (!file)
		throw FgsmException("Can not open parameters file");

	layers = std::list<Layer*>();
	for (int i = 0; i < HIDDEN_LAYERS + 2 ; i++) {
		if (i == 0)
			layers.push_back(new Layer(file, INPUT_WIDTH, HIDDEN_WIDTH));
		else if (i == HIDDEN_LAYERS + 1)
			layers.push_back(new Layer(file, HIDDEN_WIDTH, OUTPUT_WIDTH, true));
		else
			layers.push_back(new Layer(file, HIDDEN_WIDTH, HIDDEN_WIDTH));
	}
	file.close();
}

Vector NeuralNetwork::forward(const Vector &input, std::stack<Vector> *outputsStack) {
	Vector tmp = input;
	for (auto it = layers.begin(); it != layers.end(); ++it) {
		tmp = (*it)->forward(tmp, outputsStack);
	}
	return tmp;
}

int NeuralNetwork::predict(const Vector &input, double *confidence) {
	Vector probVector(forward(input)); 
	return probVector.argmax(confidence) + 1;
}

void NeuralNetwork::printPrediction(const Vector &input) {
	double confidence = 0;
	int label = predict(input, &confidence);
	printf("predict label %d (confidence : %.3f)\n", label, confidence);
}

Pgm NeuralNetwork::attack(Pgm &input, int label, enum ATTACK_TYPE type) {
	Vector noise;

	if (type == FGSM_NOISE || type == FGSM_B_NOISE)
		noise = fgsm(input, label);
	else
		noise = Vector::randomVector(input.getSize(), -1, 1);

	if (type == FGSM_NOISE || type == RANDOM_NOISE)
		return input.addNoise(noise);
	else
		return input.binarizedNoise(noise);
}

void NeuralNetwork::attack(Data &data, enum ATTACK_TYPE type) {
	Vector noise;

	if (type == FGSM_NOISE)
		data.addNoise(*this);
	else if (type  == FGSM_B_NOISE)
		data.binarizedNoise(*this);
	else if (type == RANDOM_NOISE)
		data.randomNoise();
	else
		data.binarizedRandomNoise();
}

Pgm NeuralNetwork::checkAttack(std::pair<int, Pgm*> data, enum ATTACK_TYPE type) {
	Pgm input = *data.second;
	int label = data.first;
	OUT << "file : " << input.getFilename() << "\n";
	OUT << "Expected label : " << label << "\n";
	OUT << "Before attack : ";
	printPrediction(input);

	Pgm attackInput = attack(input, label, type);
	OUT << "After attack (without binarize protection) : ";
	printPrediction(attackInput);

	OUT << "After attack (with binarize protection) : ";
	printPrediction(attackInput.binarize());
	return attackInput;
}

void NeuralNetwork::checkAttack(Data &data, enum ATTACK_TYPE type) {
	OUT << "Before attack :\n";
	data.accuracy(*this);
	
	attack(data, type);
	OUT << "After attack (without binarize protection) :\n";
	data.accuracy(*this);

	data.binarize();
	OUT << "After attack (with binarize protection) :\n";
	data.accuracy(*this);
}

Vector NeuralNetwork::backward(const Vector &delta, const Vector &output) {
	Vector result(delta.getSize());
	for (int i = 0; i < delta.getSize(); i++) {
		if (output[i] > 0)
			result[i] = delta[i];
	}
	return result;
}

Vector NeuralNetwork::fgsm(Vector &input, int label) {
	std::stack<Vector> outputsStack = std::stack<Vector>();
	Vector oneHotLabels = Vector::oneHotVector(OUTPUT_WIDTH, label);
	Vector probs = forward(input, &outputsStack);
	Vector delta = probs - oneHotLabels;
	for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
		if (outputsStack.size() > 0) {
			delta = backward((*it)->weights.transpose() * delta, outputsStack.top());
			outputsStack.pop();
		} else {
			delta = (*it)->weights.transpose() * delta;
		}
	}
	return delta;
}

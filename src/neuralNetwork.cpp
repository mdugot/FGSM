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

Vector NeuralNetwork::forward(Vector &input, std::stack<Vector> *outputsStack) {
	Vector tmp = input;
	for (auto it = layers.begin(); it != layers.end(); ++it) {
		tmp = (*it)->forward(tmp, outputsStack);
	}
	return tmp;
}

int NeuralNetwork::predict(Vector &input) {
	Vector probVector(forward(input)); 
	return probVector.argmax() + 1;
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

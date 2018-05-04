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

Vector Layer::forward(Vector &input) {
	Vector result = weights * input + biais;
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

Vector NeuralNetwork::forward(Vector &input) {
	
	Vector tmp = input;
	for (auto it = layers.begin(); it != layers.end(); ++it) {
		tmp = (*it)->forward(tmp).relu();
	}
	return tmp;
}

int NeuralNetwork::predict(Vector &input) {
	
	Vector probVector(forward(input)); 
	return probVector.argmax() + 1;
}

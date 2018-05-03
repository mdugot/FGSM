#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "matrix.h"
#include "vector.h"
#include <list>

#define PARAM_FILE "param.txt"
#define HIDDEN_LAYERS 1
#define INPUT_WIDTH 1024
#define HIDDEN_WIDTH 256
#define OUTPUT_WIDTH 23

class Layer
{
	private:

		Vector biais;
		Matrix weights;
		bool lastLayer;

	public:

		Layer(std::ifstream &file, int inputSize, int outputSize, bool last = false);
		~Layer();
		Vector forward(Vector &input);
};

class NeuralNetwork
{
	private:

		std::list<Layer*> layers;

	public:

		NeuralNetwork();
		~NeuralNetwork();
		Vector forward(Vector &input);
		int predict(Vector &input);
};

#endif

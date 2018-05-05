#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "matrix.h"
#include "pgm.h"
#include "data.h"
#include <list>
#include <stack>

#define PARAM_FILE "param.txt"
#define HIDDEN_LAYERS 1
#define INPUT_WIDTH 1024
#define HIDDEN_WIDTH 256
#define OUTPUT_WIDTH 23

enum ATTACK_TYPE {
	FGSM_NOISE, RANDOM_NOISE, FGSM_B_NOISE, RANDOM_B_NOISE
};

class Layer
{
	friend class NeuralNetwork;

	private:

		Vector biais;
		Matrix weights;
		bool lastLayer;

	public:

		Layer(std::ifstream &file, int inputSize, int outputSize, bool last = false);
		~Layer();
		Vector forward(Vector &input, std::stack<Vector> *outputsStack = NULL);
};

class NeuralNetwork
{
	private:

		std::list<Layer*> layers;

	public:

		NeuralNetwork();
		~NeuralNetwork();
		Vector forward(const Vector &input, bool binarize, std::stack<Vector> *outputsStack = NULL);
		Vector backward(const Vector &delta, const Vector &outputs);
		int predict(const Vector &input, bool binarize, double *confidence = NULL);
		void printPrediction(const Vector &input, bool binarize);
		Vector fgsm(Vector &input, int label);

		Pgm checkAttack(std::pair<int, Pgm*> data, enum ATTACK_TYPE type);
		Pgm attack(Pgm &input, int label, enum ATTACK_TYPE type);
		void attack(Data &data, enum ATTACK_TYPE type);
		void checkAttack(Data &data, enum ATTACK_TYPE type);
};

#endif

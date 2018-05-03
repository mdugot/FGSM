#include "neuralNetwork.h"
#include "data.h"

int main(int argc, char **argv) {

	Data data("./pgm");
	NeuralNetwork nn;

	Pgm pgm("./pgm/2.pgm");
	DEBUG << "Predict => " << nn.predict(pgm) << "\n";
}

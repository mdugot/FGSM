#include "neuralNetwork.h"
#include "data.h"

int main(int argc, char **argv) {

	Data data("./pgm");
	NeuralNetwork nn;

	Pgm pgm("./pgm/1.pgm");
	Vector probs = nn.forward(pgm);
	probs.print();
	DEBUG << "Predict => " << nn.predict(pgm) << "\n";
	data.accuracy(nn);
}

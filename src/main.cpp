#include "neuralNetwork.h"
#include "data.h"

int main(int argc, char **argv) {

	Data data("./pgm");
	NeuralNetwork nn;

//	Pgm pgm("./pgm/1.pgm");
//
//	Vector probs = nn.forward(pgm);
//	probs.print();
//
//	DEBUG << "Predict => " << nn.predict(pgm) << "\n";
//	data.accuracy(nn);
//
//	Vector noise = nn.fgsm(pgm, 15);
//	noise.print(10);
//
//	data.addNoise(nn);
//	data.save("./noisePgm");
//	data.accuracy(nn);

	DEBUG << "WITHOUT NOISE\n";
	Pgm pgm("./pgm/1.pgm");
	Vector probs = nn.forward(pgm);
	probs.print(8);

	DEBUG << "WITH NOISE\n";
	Pgm npgm("./noisePgm/1.pgm");
	Vector nprobs = nn.forward(npgm);
	nprobs.print(8);
}

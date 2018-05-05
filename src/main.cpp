#include "neuralNetwork.h"
#include "data.h"

void help() {
	ERR << "\nUSAGE\n";
	ERR << "./attack <type> <target> [<save to>]\n";
	ERR << "\nTYPE\n";
	ERR << "fgsm            : generate noise with the Fast Gradient Sign Method\n";
	ERR << "random          : generate random noise\n";
	ERR << "random-binarize : switch (0 to 1 or 1 to 0) randomly 1% of the inputs\n";
	ERR << "fgsm-binarize   : use Gradient Descent to get inputs gradients then switch the 1% steepest inputs\n";
	ERR << "\nTARGET\n";
	ERR << "random     : pick a random image file in the 'pgm' directory\n";
	ERR << "all        : check all the images in the 'pgm' directory\n";
	ERR << "<filename> : select a specific file\n\n";
	ERR << "\nSAVE TO (optional)\n";
	ERR << "If target is 'all', indicate the repertory where to save all the modified images.\n";
	ERR << "Else, indicate the file name used to save the target image.\n";
	ERR << "If not present, the modified image(s) are not saved.\n\n";
}

enum ATTACK_TYPE getAttackType(std::string arg) {
	if (arg == "fgsm")
		return FGSM_NOISE;
	else if (arg == "fgsm-binarize")
		return FGSM_B_NOISE;
	else if (arg == "random")
		return RANDOM_NOISE;
	else if (arg == "random-binarize")
		return RANDOM_B_NOISE;
	throw FgsmException("attack type not recognize. Possible choices : fgsm, fgsm-binarize, random, random-binarize.");
}

int main(int argc, char **argv) {

	try {
		srand(time(NULL));
		Data data("./pgm");
		NeuralNetwork nn;

		if (argc < 3 || argc > 4) {
			help();
			return 1;
		}

		enum ATTACK_TYPE type = getAttackType(argv[1]);
		std::string target(argv[2]);
		std::string saveTo("");
		if (argc == 4)
			saveTo = argv[3];
		
		if (target == "all") {
			nn.checkAttack(data, type);
			if (saveTo.size() > 0) {
				data.save(saveTo);
			}
		} else {
			std::pair<int, Pgm*> d;
			if (target == "random") {
				d = data.randomData();
			} else {
				d = data.findData(target);
			}
			Pgm modified = nn.checkAttack(d, type);
			if (saveTo.size() > 0) {
				modified.save(saveTo);
			}
		}
		
		return 0;
	} catch (FgsmException e) {
		ERR << "ERROR - " << e.what() << "\n";
		return 1;
	}
}

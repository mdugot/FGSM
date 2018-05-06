#include "neuralNetwork.h"
#include "data.h"

void help() {
	ERR << "\nUSAGE\n";
	ERR << "./attack [-a <type>] [-t <target>] [-s <save to>]\n";
	ERR << "\n-a\n";
	ERR << "fgsm            : (DEFAULT) generate noise with the Fast Gradient Sign Method\n";
	ERR << "random          : generate random noise\n";
	ERR << "random-binarize : switch (0 to 1 or 1 to 0) randomly 1% of the inputs\n";
	ERR << "fgsm-binarize   : use Gradient Descent to get inputs gradients then switch the 1% steepest inputs\n";
	ERR << "\n-t\n";
	ERR << "all        : (DEFAULT) check all the images in the 'pgm' directory\n";
	ERR << "random     : pick a random image file in the 'pgm' directory\n";
	ERR << "<filename> : select a specific file\n\n";
	ERR << "\n-s\n";
	ERR << "If target is 'all', indicate the repertory where to save all the modified images.\n";
	ERR << "Else, indicate the file name used to save the target image.\n";
	ERR << "If not present, by default, the modified image(s) are not saved.\n\n";
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
		int c;
		srand(time(NULL));
		enum ATTACK_TYPE type = FGSM_NOISE;
		std::string target = "all";
		std::string saveTo = "";
  		while ((c = getopt (argc, argv, "a:t:s:")) != -1) {
			switch (c) {
				case 'a':
					type = getAttackType(optarg);
				break;
				case 't':
					target = optarg;
				break;
				case 's':
					saveTo = optarg;
				break;
				case '?':
				default:
					help();
					return 1;
				break;
			}
		}
		if (optind < argc) {
			help();
			return 1;
		}
		Data data("./pgm");
		NeuralNetwork nn;
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

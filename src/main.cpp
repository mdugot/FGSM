#include "neuralNetwork.h"
#include "data.h"

int main(int argc, char **argv) {

	try {
		int c;
		srand(time(NULL));
		enum ATTACK_TYPE type = FGSM_NOISE;
		std::string target = "all";
		std::string saveTo = "";
  		while ((c = getopt(argc, argv, "r:e:a:t:s:uh")) != -1) {
			switch (c) {
				case 'a':
					type = getAttackType(optarg);
				break;
				case 'u':
					unitest();
					return 0;
				break;
				case 't':
					target = optarg;
				break;
				case 's':
					saveTo = optarg;
				break;
				case 'e':
					try {
						Pgm::epsilon = std::stod(optarg);
					} catch (std::invalid_argument e) {
						throw FgsmException("-e option has to be a number.");
					}
				break;
				case 'r':
					try {
						Pgm::ratio = std::stod(optarg);
					} catch (std::invalid_argument e) {
						throw FgsmException("-r option has to be a number.");
					}
				break;
				case 'h':
					help();
					return 0;
				break;
				case '?':
				default:
					usage();
					return 1;
				break;
			}
		}
		if (optind < argc) {
			usage();
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

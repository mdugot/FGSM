#include "tools.h"
#include "fgsmException.h"

void help() {
	ERR << "\nUSAGE\n";
	ERR << "./attack [-a <type>] [-t <target>] [-s <save to>] [-u]\n";
	ERR << "\n-a\n";
	ERR << "fgsm            : (DEFAULT) generate noise with the Fast Gradient Sign Method\n";
	ERR << "random          : generate random noise\n";
	ERR << "random-binarize : switch (0 to 1 or 1 to 0) randomly 1% of the inputs\n";
	ERR << "fgsm-binarize   : use Gradient Descent to get inputs gradients then switch the 1% steepest inputs\n";
	ERR << "none            : No attack, print only original accuracy or prediction\n";
	ERR << "\n-t\n";
	ERR << "all        : (DEFAULT) check all the images in the 'pgm' directory\n";
	ERR << "random     : pick a random image file in the 'pgm' directory\n";
	ERR << "<filename> : select a specific file\n\n";
	ERR << "\n-s\n";
	ERR << "If target is 'all', indicate the repertory where to save all the modified images.\n";
	ERR << "Else, indicate the file name used to save the target image.\n";
	ERR << "If not present, by default, the modified image(s) are not saved.\n";
	ERR << "\n-u\n";
	ERR << "Conduct unitest on vector/matrix operations (sum, product, transpose, relu, softmax...).\n\n";
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
	else if (arg == "none")
		return NO_ATTACK;
	throw FgsmException("attack type not recognize. Possible choices : fgsm, fgsm-binarize, random, random-binarize.");
}


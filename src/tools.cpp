#include "tools.h"
#include "fgsmException.h"

void usage() {
	ERR << "USAGE\n";
	ERR << "./attack [-a <type>] [-t <target>] [-s <save to>] [-e <epsilon>] [-r <ratio>] [-uh]\n";
}
void help() {
	usage();
	ERR << "\n-a <type>\n";
	ERR << "fgsm            : (DEFAULT) generate noise with the Fast Gradient Sign Method\n";
	ERR << "random          : generate random noise\n";
	ERR << "random-binarize : reverse (0 to 1 or 1 to 0) randomly a small proportion of the inputs\n";
	ERR << "fgsm-binarize   : use Gradient Descent to get inputs gradients then switch the steepest inputs\n";
	ERR << "none            : No attack, print only original accuracy or prediction\n";
	ERR << "\n-t <target>\n";
	ERR << "all        : (DEFAULT) check all the images in the 'pgm' directory\n";
	ERR << "random     : pick a random image file in the 'pgm' directory\n";
	ERR << "<filename> : select a specific file (example: '-t 12.pgm')\n";
	ERR << "\n-s <save to>\n";
	ERR << "If target is 'all', indicate the repertory where to save all the modified images.\n";
	ERR << "Else, indicate the file name used to save the target image.\n";
	ERR << "If not present, by default, the modified image(s) are not saved.\n";
	ERR << "\n-e <epsilon>\n";
	ERR << "Used by fgsm and random methods.\n";
	ERR << "Set the epsilon value that define the noise intensity.\n";
	ERR << "Default is 0.1.\n";
	ERR << "\n-r <ratio>\n";
	ERR << "Used by fgsm-binarize and random-binarize methods.\n";
	ERR << "Set the ratio of pixels that will be reverse.\n";
	ERR << "Default is 0.01 (corresponds to a proportion of 1%).\n";
	ERR << "\n-h\n";
	ERR << "Display help.\n";
	ERR << "\n-u\n";
	ERR << "Conduct unitest on vector/matrix operations (sum, product, transpose, relu, softmax...).\n";
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


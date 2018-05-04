#include "pgm.h"

Pgm::Pgm(void) : Vector(), w(0), h(0), maxWhite(0) {}

Pgm::Pgm(const Pgm &from) : Vector(from) {
	w = from.getW();
	h = from.getH();
	maxWhite = from.getMaxWhite();
	filename = from.getFilename();
}

Pgm::Pgm(std::string filename) : Vector() {

	int pos = filename.find_last_of('/');
	this->filename = filename.substr(pos + 1);
	std::ifstream file(filename);
	if (!file)
		throw FgsmException("Can not open pgm file : " + filename);
	std::string tmp;
	file >> tmp;
	if (tmp != "P2")
		throw FgsmException("malformed pgm file : " + filename);
	file >> w >> h >> maxWhite;
	values = new double[w*h];
	size = w*h;
	for (int i = 0; i < w*h; i++) {
		file >> values[i];
		values[i] = values[i] / (double)maxWhite;
	}
	file.close();
}

Pgm::~Pgm() {
}

void Pgm::save(std::string filename) {
	std::ofstream file(filename);
	if (!file)
		throw FgsmException("Can not open pgm file : " + filename);
	file << "P2\r\n";
	file << w << " " << h << "\r\n";
	file << maxWhite << "\r\n";
	int tmp;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (j > 0)
				file << " ";
			tmp = (values[i*w + j] * maxWhite);
			if (tmp < 0)
				tmp = 0;
			if (tmp > maxWhite)
				tmp = maxWhite;
			file << tmp;
		}
		file << "\r\n";
	}
	file.close();
}

void Pgm::addNoise(Vector &noise, double epsilon) {
	for (int i = 0; i < size; i++) {
		if (noise[i] > 0)
			values[i] += epsilon;
		else
			values[i] -= epsilon;
	}
}

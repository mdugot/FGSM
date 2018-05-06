#ifndef DATA_H
#define DATA_H

#include "pgm.h"
#include <dirent.h>
#include <unordered_map>
#include <vector>
#include <sys/stat.h>

#define LABEL_FILE "labels.txt"

class NeuralNetwork;

class Data
{
	private:

		std::unordered_multimap<int, Pgm*> all;

	public:

		Data(std::string foldername);
		~Data();

		int size() {return all.size();}
		void accuracy(NeuralNetwork &nn, bool binarize);
		void addNoise(NeuralNetwork &nn);
		void randomNoise();
		void binarizedNoise(NeuralNetwork &nn);
		void binarizedRandomNoise();
		void save(std::string foldername);

		std::pair<int, Pgm*> randomData();
		std::pair<int, Pgm*> findData(std::string name);
};

#endif

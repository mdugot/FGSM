#ifndef DATA_H
#define DATA_H

#include "pgm.h"
#include "neuralNetwork.h"
#include <dirent.h>
#include <unordered_map>
#include <vector>

#define LABEL_FILE "labels.txt"

class Data
{
	private:

		std::unordered_multimap<int, Pgm*> all;

	public:

		Data(std::string foldername);
		~Data();

		int size() {return all.size();}
		void accuracy(NeuralNetwork &nn);
};

#endif

#include "data.h"

bool isPgmFile(std::string filename) {
	if (filename[0] == '.')
		return false;
	if (filename.find(".pgm") == filename.size() - 4)
		return true;
	return false;
}

int getFileIndex(std::string filename) {
	return std::stoi(filename) - 1;
}

Data::Data(std::string foldername) {

	std::vector<int> labels;
	all = std::unordered_multimap<int, Pgm*>();
	std::ifstream labelfile(LABEL_FILE);
	if (!labelfile)
		throw FgsmException("Can not open labels file");
	int tmp;
	while (labelfile >> tmp) {
		labels.push_back(tmp);
	}

	struct dirent *entry;
	DIR *folder = opendir(foldername.c_str());
	if (!folder)
		throw FgsmException("can not open data folder : " + foldername);
	while ((entry = readdir(folder))) {
		std::string filename(entry->d_name);
		if (isPgmFile(filename)) {
			tmp = labels[getFileIndex(filename)];
			all.insert(std::pair<int, Pgm*>(tmp, new Pgm(foldername + "/" + filename)));
		}
	}
	labelfile.close();
}

Data::~Data() {
	for (auto it = all.begin(); it != all.end(); ++it) {
		delete it->second;
	}
}

void Data::accuracy(NeuralNetwork &nn) {
	int success = 0;
	int prediction;
	for (auto it = all.begin(); it != all.end(); ++it) {
		prediction = nn.predict(*(it->second));
		//DEBUG << "prediction : " << prediction << " vs " << it->first << "\n";
		if (prediction == it->first)
			success++;
	}
	OUT << "Succes : " << success << " / " << all.size() << "\n";
	int percent = (double)success / (double)all.size() * 100.0;
	OUT << "Accuracy : " << percent << "%\n";
}

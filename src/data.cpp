#include "data.h"

bool isPgmFile(std::string filename) {
	if (filename[0] == '.')
		return false;
	if (filename.find(".pgm") == filename.size() - 4)
		return true;
	return false;
}

Data::Data(std::string foldername) {

	all = std::unordered_multimap<int, Pgm*>();
	std::ifstream labelfile(LABEL_FILE);
	if (!labelfile)
		throw FgsmException("Can not open labels file");
	struct dirent *entry;
	DIR *folder = opendir(foldername.c_str());
	if (!folder)
		throw FgsmException("can not open data folder : " + foldername);
	int label = 0;
	while ((entry = readdir(folder))) {
		std::string filename(entry->d_name);
		if (isPgmFile(filename)) {
			labelfile >> label;
			all.insert(std::pair<int, Pgm*>(label, new Pgm(foldername + "/" + filename)));
		}
	}
	labelfile.close();
}

Data::~Data() {
	for (auto it = all.begin(); it != all.end(); ++it) {
		//delete it->second;
	}
}

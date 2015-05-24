
#include "FileUtils.h"

namespace utils {

uint64_t saveFile(std::string name, std::string content) {
	std::ofstream file(name);
	file << content;
	file.close();
	return 0;
}

void loadInJMol(std::string filePath) {
	std::string command = "C:/jmol/jmol.jar " + filePath;
	system(command.c_str());
}

}
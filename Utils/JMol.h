#include "StlBase.h"

namespace utils {

void loadInJMol(std::string filePath) {
	std::string command = "C:/jmol/jmol.jar " + filePath;
	system(command.c_str());
}

}
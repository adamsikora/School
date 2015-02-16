#pragma once

#include "StlBase.h"

namespace utils {

	uint64_t saveFile(std::string name, std::string content) {
		std::ofstream file(name);
		file << content;
		file.close();
		return 0;
	}

}

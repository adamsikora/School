#pragma once

#include <memory>
#include <assert.h>
#include <cstddef>

#include <limits>

uint64_t binToGray(uint64_t bin) {
	return bin ^ (bin / 2);
}

uint64_t grayToBin(uint64_t gray) {
	gray ^= gray >> 32;
	gray ^= gray >> 16;
	gray ^= gray >> 8;
	gray ^= gray >> 4;
	gray ^= gray >> 2;
	gray ^= gray >> 1;
	return gray;
}
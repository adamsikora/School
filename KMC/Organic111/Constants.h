#pragma once

#include "StlBase.h"


namespace c {
	const int64_t w = 64;
	const int64_t h = w;
	const int64_t A = w * h;

	const int64_t maxBoundCount = 16;

	const int64_t empty = -1;

	const int64_t nRotations = 3;
	const int64_t nDiffusions = 6;

	const int64_t seed = 13;

	const double adsRate = 0.000001;

	const double E_b = 0.55;
	const double E_d = 0.55;
	const double boltzmann = 8.6173324e-5;
	const double nu = 1e13;
	const double T = 300.0;

	const double finalTime = 1.0;
}
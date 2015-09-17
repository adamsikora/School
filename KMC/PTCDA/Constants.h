#pragma once

#include "StlBase.h"


namespace c {
	const int64_t w = 256;
	const int64_t h = w / 4;
	const int64_t A = w * h;

	const int64_t boundTypesBin = 3;
	const int64_t boundTypes = 1i64 << boundTypesBin;
	const int64_t boundsPerType = 4;
	const int64_t maxBoundCount = 1i64 << (boundTypesBin * boundsPerType);
	const int64_t realBoundTypes = 6; // five configurations + no bound

	const int64_t empty = -1;
	const int64_t molec = 0;

	const int64_t nDiffusions = 2;

	const int64_t seed = 13;

	const int64_t ptcdaLength = 4;
	const int64_t ptcdaWidth = 4;
	const int64_t ptcdaBondLength = 5;

	const double boltzmann = 8.6173324e-5;

	const double adsRate = 0.01 / 60 / (ptcdaLength);

	const std::array<double, c::boundTypes> E_b{ { 0.0, -0.500, -0.192, 0.507, -0.174, -0.136 } }; // no bound, centered, centered - 1...

	const double E_d = 1.1;
	const double nu = 1e13;
	const double T = 273.14 + 220;

	const double finalTime = 0.0;
	const double finalCoverage = 0.2;

	const std::array<int64_t, c::nDiffusions> defaultDiffusions{ { c::empty, c::empty } };
}
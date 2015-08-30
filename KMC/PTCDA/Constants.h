#pragma once

#include "StlBase.h"


namespace c {
	const int64_t w = 64;
	const int64_t h = w;
	const int64_t A = w * h;

	const int64_t maxBoundPerType = 16;
	const int64_t maxBoundCount = maxBoundPerType*maxBoundPerType*maxBoundPerType;
	inline int64_t getBoundCount(int64_t N_N, int64_t N_O, int64_t O_O) { return N_N * c::maxBoundPerType*c::maxBoundPerType + N_O * c::maxBoundPerType + O_O; }

	const int64_t empty = -1;

	const int64_t nRotations = 3;
	const int64_t nDiffusions = 6;

	const int64_t seed = 13;

	const double adsRate = 0.002;

	const double E_bnn = 0.1;
	const double E_bno = 0.8;
	const double E_boo = -0.3;
	const double E_d = 0.7;
	const double boltzmann = 8.6173324e-5;
	const double nu = 1e13;
	const double T = 300.0;

	const double finalTime = 10.0;

	const std::array<int64_t, c::nDiffusions> defaultDiffusions{ { c::empty, c::empty, c::empty, c::empty, c::empty, c::empty } };
	const std::array<int64_t, c::nRotations>  defaultRotations{ { c::empty, c::empty, c::empty } };
}
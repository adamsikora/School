#pragma once

#include "Constants.h"
#include "BaseClass.h"

class Events;

class Rates {
public:
	Rates(double E_d) : _ads(c::adsRate) {
		for (int64_t i = 0; i < c::maxBoundCount; i++) {
			_diff[i] = 0;
			_sumsofDiff[i] = 0;
			_sumsofRot[i] = 0;
		}
		_totalAds = _totalDiff = _total = 0;
		_setRates(E_d);
	}

	friend class Events;

private:
	double _ads;
	double _diff[c::maxBoundCount];

	double _sumsofDiff[c::maxBoundCount], _sumsofRot[c::maxBoundCount];
	double _totalAds, _totalDiff;
	double _total;

	void _checkRates() {
		for (int64_t i = 0; i < c::boundTypes; ++i) {
			for (int64_t j = i; j < c::boundTypes; ++j) {
				for (int64_t k = j; k < c::boundTypes; ++k) {
					for (int64_t l = k; l < c::boundTypes; ++l) {
						std::vector<int64_t> indeces{ i, j, k, l };
						bool shouldBeInvalid =
							(i >= c::realBoundTypes) ||
							(j >= c::realBoundTypes) ||
							(k >= c::realBoundTypes) ||
							(l >= c::realBoundTypes);
						int64_t index = 0;
						for (auto it : indeces) {
							index += it;
							index *= c::boundTypes;
						}
						assert(index % c::boundTypes == 0);
						index /= c::boundTypes;
						assert(index < c::maxBoundCount);
						double bound = _diff[index];
						assert(!(shouldBeInvalid ^ std::isnan(_diff[index])));

						while (std::next_permutation(indeces.begin(), indeces.end())) {
							int64_t index = 0;
							for (auto it : indeces) {
								index += it;
								index *= c::boundTypes;
							}
							assert(index % c::boundTypes == 0);
							index /= c::boundTypes;
							assert(index < c::maxBoundCount);
							assert(!(abs(bound - _diff[index]) > 1e-6*(bound + _diff[index])));
							assert(!(shouldBeInvalid ^ std::isnan(_diff[index])));
						}
					}
				}
			}
		}
	}

	void _setRates(double E_d) {
		_ads = c::adsRate;
		for (int64_t i = 0; i < c::maxBoundCount; ++i) {
			double E_bound = 0;
			for (int64_t j = 0; j < c::boundsPerType; ++j) {
				int64_t bound = (i >> (j*c::boundTypesBin)) % c::boundTypes; //here
				if (bound < c::realBoundTypes) {
					E_bound += c::E_b[bound]; // check this
				} else {
					E_bound = std::numeric_limits<double>::quiet_NaN();
				}
			}
			
			_diff[i] = std::isnan(E_bound) ? std::numeric_limits<double>::quiet_NaN() : c::nu * exp(-(E_bound + E_d) / (c::boltzmann * c::T));
		}
		_checkRates();
	}

	void _setSums(std::vector<DiffusionEvent>* diff) {
		_totalDiff = _total = 0;
		_totalAds = _ads * c::A;

		for (int i = 0; i < c::maxBoundCount; i++) {
			if (!diff[i].empty() && !std::isnan(_diff[i]))
				_totalDiff += _sumsofDiff[i] = _diff[i] * diff[i].size();
			else
				_sumsofDiff[i] = 0;
		}

		_total = _totalAds + _totalDiff;
	}

};
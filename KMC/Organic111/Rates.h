#pragma once

#include "Constants.h"
#include "Molecule.h"

class Events;

class Rates {
public:
	Rates() : _ads(c::adsRate) {
		for (int64_t i = 0; i < c::maxBoundCount; i++) {
			_diff[i] = 0;
			_rot[i] = 0;
			_sumsofDiff[i] = 0;
			_sumsofRot[i] = 0;
		}
		_totalAds = _totalDiff = _totalRot = _total = 0;
		_setRates();
	}

	friend class Events;

private:
	double _ads;
	double _diff[c::maxBoundCount], _rot[c::maxBoundCount];

	double _sumsofDiff[c::maxBoundCount], _sumsofRot[c::maxBoundCount];
	double _totalAds, _totalDiff, _totalRot;
	double _total;

	void _setRates() {
		_ads = c::adsRate;
		for (int64_t i = 0; i < c::maxBoundPerType; ++i) {
			for (int64_t j = 0; j < c::maxBoundPerType; ++j) {
				for (int64_t k = 0; k < c::maxBoundPerType; ++k) {
					int64_t boundCount = c::getBoundCount(i, j, k);
					_diff[boundCount] = _rot[boundCount] = c::nu * exp(-(i * c::E_bnn + j * c::E_bno + k * c::E_boo + c::E_d) / (c::boltzmann * c::T));
				}
			}
		}
	}

	void _setSums(std::vector<DiffusionEvent>* diff, std::vector<RotationEvent>* rot) {
		_totalRot = _totalDiff = _total = 0;
		_totalAds = _ads * c::A;

		for (int i = 0; i < c::maxBoundCount; i++) {
			if (!rot[i].empty())
				_totalRot += _sumsofRot[i] = _rot[i] * rot[i].size();
			else
				_sumsofRot[i] = 0;

			if (!diff[i].empty())
				_totalDiff += _sumsofDiff[i] = _diff[i] * diff[i].size();
			else
				_sumsofDiff[i] = 0;
		}

		_total = _totalAds + _totalDiff + _totalRot;
	}

};
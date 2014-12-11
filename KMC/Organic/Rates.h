/*

*/

#ifndef RATES_H
#define RATES_H

#include "Includes.h"

class Events;

class Rates
{
public:
	Rates() : _ads(c::adsRate)
	{
		for (int i = 0; i < c::maxBoundCount; i++) {
			_diff[i] = 0;
			_rot[i] = 0;
			_sumsofDiff[i] = 0;
			_sumsofRot[i] = 0;
		}
		_totalAds = _totalDiff = _totalRot = _total = 0;
	}

	friend class Events;

private:
	double _ads;
	double _diff[c::maxBoundCount], _rot[c::maxBoundCount];

	double _sumsofDiff[c::maxBoundCount], _sumsofRot[c::maxBoundCount];
	double _totalAds, _totalDiff, _totalRot;
	double _total;

	void _setRates()
	{
		_ads = c::adsRate;
		for (int i = 0; i < c::boundsSep; i++)
		for (int j = 0; j < c::boundsSep; j++)
		for (int k = 0; k < c::boundsSep; k++) {
			int index = i + j * c::boundsSep + k * c::boundsSep * c::boundsSep;
			_diff[index] = _rot[index] = c::nu * exp(-(i * c::ligInter11 + j * c::ligInter12 + k * c::ligInter22 + c::E_b) / (c::boltzmann * c::T));
		}
	}

	void _setSums(std::vector<MoleculeDiffEvent>* diff, std::vector<MoleculeRotEvent>* rot)
	{
		_totalRot = _totalDiff = _total = 0;
		_totalAds = _ads * c::A;

		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		for (int k = 0; k < 5; k++) {
			const int ci = i + j * c::boundsSep * c::boundsSep + k * c::boundsSep;
			if (!rot[ci].empty())
				_totalRot += _sumsofRot[ci] = _rot[ci] * rot[ci].size();
			else
				_sumsofRot[ci] = 0;

			if (!diff[ci].empty())
				_totalDiff += _sumsofDiff[ci] = _diff[ci] * diff[ci].size();
			else
				_sumsofDiff[ci] = 0;
		}

		_total = _totalAds + _totalDiff + _totalRot;
	}

};

#endif //RATES_H
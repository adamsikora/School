#pragma once

#include "TspBase.h"

class KohonenMapTsp : TspBase {
public:
	KohonenMapTsp(PointVector points, int64_t seed = 1) : TspBase(points, seed) {
		init();
	};
	virtual double findShortestPath() final;
	void plotInMatlab();

private:
	void init();
	PointVector _kohonenPoints;
	int64_t _nKohonenPoints;
	double _nu, _sigma, _factor;
};
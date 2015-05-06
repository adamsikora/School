#pragma once

#include "TspBase.h"

class KohonenMapTsp : TspBase {
public:
	KohonenMapTsp(PointVector points) : TspBase(points) {
		init();
	};
	virtual double findShortestPath() final;

private:
	void init();
	PointVector _kohonenPoints;
	int64_t _nKohonenPoints;
	double _nu, _sigma, _factor;
};
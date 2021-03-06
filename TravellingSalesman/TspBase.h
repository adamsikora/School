#pragma once

#include "StlBase.h"
#include "RandomUtils.h"
#include "MatlabEngine.h"

#define SHOW_OUTPUT

typedef std::pair<double, double> Point;
typedef std::vector<std::pair<double, double>> PointVector;

class TspBase {
public:
	TspBase(PointVector points, int64_t seed = 1) : _points(points), _nPoints(points.size()), _seed(seed) {};
	virtual double findShortestPath() = 0;
	double pointDistance(Point f, Point s) {
		return sqrt(pow(f.first - s.first, 2) + pow(f.second - s.second, 2));
	}

protected:
	PointVector _points;
	int64_t _nPoints;
	int64_t _seed;
};
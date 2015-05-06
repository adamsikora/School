#pragma once

#include "StlBase.h"
#include "RandomUtils.h"
#include "MatlabEngine.h"

typedef std::pair<double, double> Point;
typedef std::vector<std::pair<double, double>> PointVector;

class TspBase {
public:
	TspBase(PointVector points) : _points(points), _nPoints(points.size()) {};
	virtual double findShortestPath() = 0;

protected:
	PointVector _points;
	int64_t _nPoints;
};
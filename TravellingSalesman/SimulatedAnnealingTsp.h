#pragma once

#include "TspBase.h"

class SimulatedAnnealingTsp : TspBase {
public:
	SimulatedAnnealingTsp(PointVector points, int64_t seed = 1) : TspBase(points, seed) {
		init();
	};
	virtual double findShortestPath() final;
	void plotInMatlab();

private:
	void init();
	double _temperature, _coolingRate;
	std::vector<int64_t> _pointOrder;

	enum class TransformTypes {
		switchTwo = 0, switchSequence = 1, pushOne = 2,
	};
	const int64_t nTransformTypes = 3;
};
#pragma once

#include "TspBase.h"

class DynamicTsp : TspBase {
public:
	DynamicTsp(PointVector points) : TspBase(points) {};
	virtual double findShortestPath() final;

private:
	std::vector<float> paths;
	std::vector<std::vector<float>> edges;

	void _iterate(int64_t nVertices, int64_t left, int64_t index, int64_t set);
};
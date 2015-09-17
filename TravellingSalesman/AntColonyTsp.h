#pragma once

#include "TspBase.h"

struct Ant {
	std::vector<int64_t> visitOrder;
	double pathLength;
};

class AntColonyTsp : TspBase {
public:
	AntColonyTsp(PointVector points, int64_t seed = 1) : TspBase(points, seed), _gen(seed) {
		init();
	};
	virtual double findShortestPath() final;
	void plotInMatlab();

private:
	void init();
	void initializeAnts();
	void antWalk();
	void pheromoneUpdate();
	void resetAnts();

	std::vector<std::vector<double>> _desirability;
	std::vector<std::vector<double>> _pheromone;
	int64_t _nAnts, _nChosenAnts, _nEpochs;
	double _alpha, _beta;
	double _pheromoneMax, _pheromoneMin;
	double _dissipationRate, _depositionStrength;

	std::vector<Ant> _ants;
	Ant _bestAnt;

	utils::random::Generator _gen;

};


#include "AntColonyTsp.h"

void AntColonyTsp::plotInMatlab() {
#ifdef SHOW_OUTPUT
	std::vector<Point> orderedPoints(_nPoints, Point());
	for (int64_t i = 0; i < _nPoints; ++i) {
		orderedPoints[i] = _points[_bestAnt.visitOrder[i]];
	}
	utils::matlab::putVariableToPlot(orderedPoints, "X", "Y");
	utils::matlab::evaluate("plot(X, Y, ':rx')");
#endif
}

double AntColonyTsp::findShortestPath() {
	for (int64_t i = 0; i < _nEpochs; ++i) {
		antWalk();
		pheromoneUpdate();
		resetAnts();
		plotInMatlab();
	}
	return _bestAnt.pathLength;
}

void AntColonyTsp::init() {
	_nEpochs = 100000;
	_nAnts = 10;
	_alpha = 1.0;
	_beta = 1.0;
	_dissipationRate = 0.95;
	_pheromoneMin = 0.01;
	_pheromoneMax = 1.0;
	_depositionStrength = 0.1;

	_pheromone = std::vector<std::vector<double>>(_nPoints, std::vector<double>(_nPoints, _pheromoneMax));
	_desirability = std::vector<std::vector<double>>(_nPoints, std::vector<double>(_nPoints, 0.0));

	for (int64_t i = 0; i < _nPoints; ++i) {
		for (int64_t j = i + 1; j < _nPoints; ++j) {
			_desirability[i][j] = _desirability[j][i] = 1 / pointDistance(_points[i], _points[j]);
		}
	}
	initializeAnts();
}

void AntColonyTsp::initializeAnts() {
	for (int64_t i = 0; i < _nAnts; ++i) {
		_ants.push_back(Ant{ std::vector<int64_t>(_nPoints, 0), std::numeric_limits<double>::max() });
	}
	_bestAnt = Ant{ std::vector<int64_t>(_nPoints, 0), std::numeric_limits<double>::max() };
}

void AntColonyTsp::resetAnts() {
	double best = _bestAnt.pathLength;		// actualize best path
	int64_t bestIndex = -1;
	for (int64_t i = 0; i < _nAnts; ++i) {
		if (_ants[i].pathLength < best) {
			best = _ants[i].pathLength;
			bestIndex = i;
		}
	}
	if (bestIndex != -1) {
		_bestAnt = _ants[bestIndex];
	}

	for (int64_t i = 0; i < _nAnts; ++i) {
		_ants[i] = Ant{ std::vector<int64_t>(_nPoints, 0), std::numeric_limits<double>::max() };
	}
}

void AntColonyTsp::antWalk() {
	for (int64_t i = 0; i < _nAnts; ++i) {
		std::vector<bool> visited(_nPoints, false);
		int64_t position, startPosition;
		position = startPosition = _gen.getIntFrom0To(_nPoints);
		visited[position] = true;
		_ants[i].visitOrder[0] = position;
		_ants[i].pathLength = 0.0;
		for (int64_t j = 1; j < _nPoints; ++j) {
			std::vector<double> possibleMoves(_nPoints, 0.0);
			double sumOfMoves = 0.0;
			for (int64_t k = 0; k < _nPoints; ++k) {
				if (!visited[k] && k != position) {
					sumOfMoves += possibleMoves[k] = pow(_desirability[k][position], _alpha) * pow(_pheromone[k][position], _beta);
				}
			}
			double choose = _gen.get01() * sumOfMoves;
			int64_t chosen = 0;
			double subSum = 0.0;
			while (subSum < choose) {
				assert(chosen < _nPoints);
				subSum += possibleMoves[chosen];
				++chosen;
			}
			--chosen;
			assert(!visited[chosen] && chosen != position);
			_ants[i].pathLength += 1 / _desirability[position][chosen];
			_ants[i].visitOrder[j] = chosen;
			position = chosen;
			visited[chosen] = true;
		}
		_ants[i].pathLength += 1 / _desirability[position][startPosition];
	}
}

void AntColonyTsp::pheromoneUpdate() {
	for (auto &row : _pheromone) {
		for (double &pher : row) {
			pher *= _dissipationRate;
		}
	}

	for (auto &ant : _ants) {
		for (int64_t i = 0; i < _nPoints; ++i) {
			_pheromone[i][(i + 1) % _nPoints] = _pheromone[(i + 1) % _nPoints][i] += _depositionStrength / ant.pathLength;
		}
	}

	for (auto &row : _pheromone) {
		for (double &pher : row) {
			if (pher > _pheromoneMax || pher < _pheromoneMin) {
				pher = _pheromoneMax;
			}
		}
	}
}
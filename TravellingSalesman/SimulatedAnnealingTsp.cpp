

#include "SimulatedAnnealingTsp.h"

void SimulatedAnnealingTsp::plotInMatlab() {
#ifdef SHOW_OUTPUT
	std::vector<Point> orderedPoints(_nPoints, Point());
	for (int64_t i = 0; i < _nPoints; ++i) {
		orderedPoints[i] = _points[_pointOrder[i]];
	}
	utils::matlab::putVariableToPlot(orderedPoints, "X", "Y");
	utils::matlab::evaluate("plot(X, Y, ':rx')");
#endif
}

double SimulatedAnnealingTsp::findShortestPath() {
	utils::random::Generator gen(_seed);
	int64_t count = 0;

	double pathLength = 0;
	for (int64_t i = 0; i < _nPoints; ++i) {
		pathLength += pointDistance(_points[_pointOrder[i]], _points[_pointOrder[(i + 1) % _nPoints]]);
	}

	while (_temperature > 0.0001) {
		if (count++ % 1000 == 0) {
			plotInMatlab();
		}

		int64_t first = gen.getIntFrom0To(_nPoints);
		int64_t second = gen.getIntFrom0To(_nPoints);
		if (first == second) {
			continue;
		}
		switch (TransformTypes(gen.getIntFrom0To(nTransformTypes))) {
			case TransformTypes::switchTwo: {
				std::swap(_pointOrder[first], _pointOrder[second]);
				double newPathLength = 0;
				for (int64_t i = 0; i < _nPoints; ++i) {
					newPathLength += pointDistance(_points[_pointOrder[i]], _points[_pointOrder[(i + 1) % _nPoints]]);
				}
				if (newPathLength <= pathLength || utils::random::decide(exp((pathLength - newPathLength) / _temperature))) {
					pathLength = newPathLength;
				} else {
					std::swap(_pointOrder[first], _pointOrder[second]);
				}
				break;
			}
			case TransformTypes::switchSequence: {
				std::vector<int64_t> newOrder = _pointOrder;
				int64_t i = first, j = second;
				while (i != j && ((j + 1) % _nPoints) != i) {
					newOrder[i] = _pointOrder[j];
					newOrder[j] = _pointOrder[i];
					i = (i + 1) % _nPoints;
					j = (j - 1 + _nPoints) % _nPoints;
				}
				double newPathLength = 0;
				for (int64_t i = 0; i < _nPoints; ++i) {
					newPathLength += pointDistance(_points[newOrder[i]], _points[newOrder[(i + 1) % _nPoints]]);
				}
				if (newPathLength <= pathLength || utils::random::decide(exp((pathLength - newPathLength) / _temperature))) {
					pathLength = newPathLength;
					_pointOrder = newOrder;
				}
				break;
			}
			case TransformTypes::pushOne: {
				std::vector<int64_t> newOrder = _pointOrder;
				int64_t i = first, afterI = (first + 1) % _nPoints;
				while (i != second) {
					newOrder[i] = _pointOrder[afterI];
					i = (i + 1) % _nPoints;
					afterI = (afterI + 1) % _nPoints;
				}
				newOrder[second] = _pointOrder[first];

				double newPathLength = 0;
				for (int64_t i = 0; i < _nPoints; ++i) {
					newPathLength += pointDistance(_points[newOrder[i]], _points[newOrder[(i + 1) % _nPoints]]);
				}
				if (newPathLength <= pathLength || utils::random::decide(exp((pathLength - newPathLength) / _temperature))) {
					pathLength = newPathLength;
					_pointOrder = newOrder;
				}
				break;
			}
		}

		_temperature *= _coolingRate;
	}


	plotInMatlab();

	return pathLength;
}

void SimulatedAnnealingTsp::init() {
	_pointOrder.reserve(_nPoints);
	for (int64_t i = 0; i < _nPoints; ++i) {
		_pointOrder.push_back(i);
	}

	_temperature = 1.0;
	_coolingRate = 0.999995;

	plotInMatlab();
}
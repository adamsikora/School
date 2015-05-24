

#include "KohonenMapTsp.h"

namespace {
	double pointDistance(Point f, Point s) {
		return sqrt(pow(f.first - s.first, 2) + pow(f.second - s.second, 2));
	}

}

void KohonenMapTsp::plotInMatlab() {
#ifndef REPORT
	utils::matlab::putVariableToPlot(_points, "X", "Y");
	utils::matlab::putVariableToPlot(_kohonenPoints, "Xk", "Yk");
	utils::matlab::evaluate("plot(X, Y, 'o', Xk, Yk, ':rx')");
#endif
}

double KohonenMapTsp::findShortestPath() {
	utils::random::Generator gen(_seed);
	int64_t count = 0;
	while (_sigma > 0.2) {
		if (count++ % 1000 == 0) {
			plotInMatlab();
		}

		const int64_t city = gen.getIntFrom0To(_nPoints);
		const Point cityPoint = _points[city];

		int64_t closestPoint = 0;
		double closestDistance = std::numeric_limits<double>::max();
		for (int64_t j = 0; j < _nKohonenPoints; ++j) {		// get point closest to chosen city
			if (pointDistance(_kohonenPoints[j], _points[city]) < closestDistance) {
				closestDistance = pointDistance(_kohonenPoints[j], _points[city]);
				closestPoint = j;
			}
		}

		for (int64_t j = 0; j < _nKohonenPoints; ++j) {
			int64_t topologicalDistance = std::min(std::abs(j - closestPoint), _nKohonenPoints - std::abs(j - closestPoint));
			//assert(topologicalDistance <= _nPoints + 1);
			double gauss = exp(-pow(topologicalDistance/_sigma, 2));
			_kohonenPoints[j].first += _nu * gauss * (cityPoint.first - _kohonenPoints[j].first);
			_kohonenPoints[j].second += _nu * gauss * (cityPoint.second - _kohonenPoints[j].second);
		}
		_nu *= _factor;
		_sigma *= _factor;

	}
	std::multimap<int64_t, int64_t> closestKohonen;
	for (int64_t i = 0; i < _nPoints; ++i) {
		int64_t closestPoint = 0;
		double closestDistance = std::numeric_limits<double>::max();
		for (int64_t j = 0; j < _nKohonenPoints; ++j) {
			if (pointDistance(_kohonenPoints[j], _points[i]) < closestDistance) {
				closestDistance = pointDistance(_kohonenPoints[j], _points[i]);
				closestPoint = j;
			}
		}
		closestKohonen.insert(std::pair<int64_t, int64_t>(closestPoint, i));
	}
	auto begin = closestKohonen.begin();
	auto iter = begin;
	auto iter2 = begin;
	++iter2;
	double result = 0.0;
	for (iter, iter2; iter != closestKohonen.end(); ++iter, ++iter2) {
		if (iter2 == closestKohonen.end()) {
			iter2 = begin;
		}
		result += pointDistance(_points[iter->second], _points[iter2->second]);
	}
	plotInMatlab();

	return result;
}

void KohonenMapTsp::init() {
	_nKohonenPoints = 2 * _nPoints;
	Point middle = Point(0, 0);
	for (auto &p : _points) {
		middle.first += p.first;
		middle.second += p.second;
	}
	middle.first /= _nPoints;
	middle.second /= _nPoints;

	double distance = 0;
	for (auto &p : _points) {
		distance += pointDistance(middle, p);
	}
	distance /= _nPoints;

	for (int64_t i = 0; i < _nKohonenPoints; ++i) {
		_kohonenPoints.emplace_back(middle.first + distance * cos(2 * 3.1415 * i / _nKohonenPoints),
																middle.second + distance * sin(2 * 3.1415 * i / _nKohonenPoints));
	}
	
	_nu = 2.0;
	_sigma = 10.0;
	_factor = 0.999995;

	plotInMatlab();
}
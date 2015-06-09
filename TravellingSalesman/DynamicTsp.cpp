

#include "DynamicTsp.h"

double DynamicTsp::findShortestPath() {
	edges = std::vector<std::vector<float>>(_nPoints, std::vector<float>(_nPoints, 0));
	for (int i = 0; i < _nPoints; ++i) {
		for (int64_t j = 0; j < _points.size(); ++j) {
			edges[i][j] = edges[j][i] = sqrt(pow(_points[i].first - _points[j].first, 2) + pow(_points[i].second - _points[j].second, 2));
		}
	}
	paths = std::vector<float>(_nPoints << _nPoints, -1);
	for (int64_t i = 0; i < _nPoints - 1; ++i) {
		int64_t index = (i << _nPoints) + (1 << i);
		paths[index] = edges[0][i + 1];
	}

	float result = std::numeric_limits<float>::max();
	for (int64_t m = 2; m < _nPoints; ++m) {
#ifdef SHOW_OUTPUT
		std::cout << m << std::endl;
#endif
		_iterate(m, m, 0, 0);
	}

	for (int i = 0; i < _nPoints - 1; ++i) {
		int64_t index = (i << _nPoints) + (1 << (_nPoints - 1)) - 1;
		assert(paths[index] != -1);
		float res = paths[index] + edges[0][i + 1];
		result = std::min(result, res);
	}
	return result;
}

void DynamicTsp::_iterate(int64_t nVertices, int64_t left, int64_t index, int64_t set) {
	if (index < _nPoints) {
		if (left > 0) {
			_iterate(nVertices, left - 1, index + 1, set + (1i64 << index));
			_iterate(nVertices, left, index + 1, set);
		} else {
			std::bitset<64> bitset(set);
			for (int j = 0; j < _nPoints - 1; ++j) {
				float path = std::numeric_limits<float>::max();
				if (bitset[j]) {
					int64_t lesserSet = set - (1i64 << j);
					std::bitset<64> lesserBitset(lesserSet);
					for (int k = 0; k < _nPoints - 1; ++k) {
						if (lesserBitset[k]) {
							int64_t index = (k << _nPoints) + lesserSet;
							assert(paths[index] != -1);
							path = std::min(path, paths[index] + edges[j + 1][k + 1]);
						}
					}
				}
				int64_t index = (j << _nPoints) + set;
				paths[index] = path;
			}
		}
	}
}
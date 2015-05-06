//#include "StlBase.h"
//#undef min
//#undef max
//
//std::vector<float> paths;
//std::vector<std::vector<float>> edges;
//
//int64_t totalv;
//
//void iterate(int64_t nVertices, int64_t left, int64_t index, int64_t set) {
//	if (index < totalv) {
//		if (left > 0) {
//			iterate(nVertices, left - 1, index + 1, set + (1i64 << index));
//			iterate(nVertices, left, index + 1, set);
//		} else {
//			std::bitset<64> bitset(set);
//			for (int j = 0; j < totalv - 1; ++j) {
//				float path = std::numeric_limits<float>::max();
//				if (bitset[j]) {
//					int64_t lesserSet = set - (1i64 << j);
//					std::bitset<64> lesserBitset(lesserSet);
//					for (int k = 0; k < totalv - 1; ++k) {
//						if (lesserBitset[k]) {
//							int64_t index = (k << totalv) + lesserSet;
//							assert(paths[index] != -1);
//							path = std::min(path, paths[index] + edges[j + 1][k + 1]);
//						}
//					}
//				}
//				int64_t index = (j << totalv) + set;
//				paths[index] = path;
//			}
//		}
//	}
//}
//
//int64_t tsp() {
//	std::ifstream input("tsp.txt");
//	if (!input.good() || !input.is_open()) {
//		std::cout << "badfile\n";
//	}
//	input >> totalv;
//
//	std::vector<std::pair<float, float>> points;
//	edges = std::vector<std::vector<float>>(totalv, std::vector<float>(totalv, 0));
//	for (int i = 0; i < totalv; ++i) {
//		float f, s;
//		input >> f;
//		input >> s;
//		for (int64_t j = 0; j < points.size(); ++j) {
//			edges[i][j] = edges[j][i] = sqrt(pow(points[j].first - f, 2) + pow(points[j].second - s, 2));
//		}
//		points.emplace_back(f, s);
//	}
//	paths = std::vector<float>(totalv << totalv, -1);
//	for (int64_t i = 0; i < totalv - 1; ++i) {
//		int64_t index = (i << totalv) + (1 << i);
//		paths[index] = edges[0][i + 1];
//	}
//
//	float result = std::numeric_limits<float>::max();
//	for (int64_t m = 2; m < totalv; ++m) {
//		std::cout << m << std::endl;
//		iterate(m, m, 0, 0);
//	}
//
//	for (int i = 0; i < totalv - 1; ++i) {
//		int64_t index = (i << totalv) + (1 << (totalv - 1)) - 1;
//		assert(paths[index] != -1);
//		float res = paths[index] + edges[0][i + 1];
//		result = std::min(result, res);
//	}
//	std::cout << result << std::endl;
//	return static_cast<int64_t>(round(result));
//}
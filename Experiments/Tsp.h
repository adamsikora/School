#include "StlBase.h"
#undef min
#undef max

class Edge {
public:
	Edge(int64_t f, int64_t s, double l) : first(f), second(s), length(l) {}
	int64_t first, second;
	double length;
};

struct Hash {
	std::size_t operator()(const std::pair<int64_t, int64_t>& pair) const {
		return std::hash<int64_t>()(pair.second * (1i64 << 32i64) + pair.first);
	}
};

std::vector<std::unordered_map<std::pair<int64_t, int64_t>, int64_t, Hash>> paths;
std::vector<std::vector<double>> edges;

int64_t totalv;

void iterate(int64_t iteration, int64_t left, int64_t curr, int64_t encoded) {
	//std::cout << std::bitset<64>(encoded) << std::endl;
	if (curr <= totalv) {
		if (left > 0) {
			iterate(iteration, left - 1, curr + 1, encoded + (1i64 << curr));
			iterate(iteration, left, curr + 1, encoded);
		} else {
			std::bitset<64> bitset(encoded);
			//std::cout << bitset << "this" << std::endl;
			for (int64_t i = 1; i <= totalv; ++i) {
				if (bitset[i]) {
					int64_t newEncoded = encoded - (1i64 << i);
					//std::cout << std::bitset<64>(encoded - (1i64 << i)) << " " << i + 1 << std::endl;
					double path = 1e100;
					std::bitset<64> newBitset(newEncoded);
					for (int64_t j = (iteration == 2 ? 0 : 1); j <= totalv; ++j) {
						if (newBitset[j]) {
							assert(paths[iteration - 1].count(std::pair<int64_t, int64_t>(newEncoded, j + 1)));
							path = std::min(path, paths[iteration - 1][std::pair<int64_t, int64_t>(newEncoded, j + 1)] + edges[i][j]);
						}
					}
					assert(path < 1e100);
					paths[iteration].emplace(std::pair<int64_t, int64_t>(encoded, i + 1), path);
				}
			}
		}
	}
}

int64_t tsp() {
	std::ifstream input("tsp.txt");
	if (!input.good() || !input.is_open()) {
		std::cout << "badfile\n";
	}
	input >> totalv;

	std::vector<std::pair<double, double>> points;
	edges = std::vector<std::vector<double>>(totalv, std::vector<double>(totalv, 0));
	for (int i = 0; i < totalv; ++i) {
		double f, s;
		input >> f;
		input >> s;
		for (int64_t j = 0; j < points.size(); ++j) {
			edges[i][j] = edges[j][i] = sqrt(pow(points[j].first - f, 2) + pow(points[j].second - s, 2));
		}
		points.emplace_back(f, s);
	}
	paths = std::vector<std::unordered_map<std::pair<int64_t, int64_t>, int64_t, Hash>>(totalv + 1, std::unordered_map<std::pair<int64_t, int64_t>, int64_t, Hash>());
	paths[1][std::pair<int64_t, int64_t>(1i64, 1i64)] = 0;

	double result = 1e100;
	//totalv = 5;
	//iterate(2, 2, 1, 1);
	for (int64_t m = 2; m <= totalv; ++m) {
		std::cout << m << std::endl;
		iterate(m, m - 1, 1, 1);
	}

	//for (int i = 2; i <= totalv; ++i) {
	//	assert(paths[totalv].count(std::pair<int64_t, int64_t>((1ui64 << totalv) - 1, i)));
	//	double res = paths[totalv][std::pair<int64_t, int64_t>((1ui64 << totalv) - 1, i)] + edges[1][i];
	//	result = std::min(result, res);
	//}

	return static_cast<int64_t>(round(result));
}
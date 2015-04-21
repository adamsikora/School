//#include "StlBase.h"
//#undef min
//
//class Edge {
//public:
//	Edge(int64_t f, int64_t s, int64_t l) : first(f), second(s), length(l) {}
//	int64_t first, second, length;
//};
//
//int64_t apsp() {
//	int64_t result = std::numeric_limits<int64_t>::max();
//	for (int files = 0; files < 4; ++files) {
//		std::stringstream ss;
//		ss << "g" << files << ".txt";
//		std::string filename = ss.str();
//		std::ifstream input(filename);
//		if (!input.good() || !input.is_open()) {
//			std::cout << "badfile\n";
//		}
//		int64_t totalv, totale;
//		input >> totalv;
//		input >> totale;
//
//		std::vector<Edge> items;
//		std::vector<std::map<int64_t, int64_t>> lengths(totalv + 1, std::map<int64_t, int64_t>());
//		for (int i = 0; i < totale; ++i) {
//			int64_t f, s, l;
//			input >> f;
//			input >> s;
//			input >> l;
//			//assert(!lengths[f].count(s));
//			lengths[s][f] = l;
//			items.emplace_back(f, s, l);
//		}
//		std::vector<std::vector<int64_t>> A(totalv + 1, std::vector<int64_t>(totalv + 1, std::numeric_limits<int64_t>::max() / 4));
//		A[0][1] = 0;
//		for (int64_t i = 1; i <= totalv; ++i) {
//			for (int64_t v = 1; v <= totalv; ++v) {
//				int64_t path = A[i - 1][v];
//				for (auto &neigh : lengths[v]) {
//					path = std::min(path, A[i - 1][neigh.first] + neigh.second);
//				}
//				A[i][v] = path;
//			}
//		}
//		bool hasCycle = false;
//		for (int64_t v = 1; v <= totalv; ++v) {
//			if (A[totalv][v] != A[totalv - 1][v]) {
//				hasCycle = true;
//				break;
//			}
//		}
//		if (hasCycle) {
//			std::cout << "has cycle\n";
//		} else {
//			std::cout << "cycle free\n";
//			int64_t interResult = std::numeric_limits<int64_t>::max();
//
//			for (int64_t source = 1; source <= totalv; ++source) {
//				std::cout << "computing shortest path from " << source;
//				std::vector<std::vector<int64_t>> A(totalv + 1, std::vector<int64_t>(totalv + 1, std::numeric_limits<int64_t>::max() / 4));
//				A[0][source] = 0;
//				for (int64_t i = 1; i < totalv; ++i) {
//					for (int64_t v = 1; v <= totalv; ++v) {
//						int64_t path = A[i - 1][v];
//						for (auto &neigh : lengths[v]) {
//							path = std::min(path, A[i - 1][neigh.first] + neigh.second);
//						}
//						A[i][v] = path;
//					}
//				}
//				for (int64_t i = 1; i <= totalv; ++i) {
//					if (i != source) {
//						interResult = std::min(interResult, A[totalv - 1][i]);
//					}
//				}
//				std::cout << "\t" << interResult << "\n";
//			}
//
//			result = std::min(result, interResult);
//		}
//	}
//
//	return result;
//}
//#include "StlBase.h"
//
//namespace {
//
//class SchedulingDiff {
//public:
//	SchedulingDiff(int64_t w, int64_t l) : weight(w), length(l) {}
//	int64_t weight, length;
//};
//
//
//bool operator<(const SchedulingDiff& lhs, const SchedulingDiff& rhs) {
//	if (lhs.weight - lhs.length != rhs.weight - rhs.length) {
//		return lhs.weight - lhs.length > rhs.weight - rhs.length;
//	} else {
//		return lhs.weight > rhs.weight;
//	}
//}
//
//class SchedulingRatio {
//public:
//	SchedulingRatio(int64_t w, int64_t l) : weight(w), length(l) {}
//	int64_t weight, length;
//};
//
//
//bool operator<(const SchedulingRatio& lhs, const SchedulingRatio& rhs) {
//	return static_cast<double>(lhs.weight) / lhs.length > static_cast<double>(rhs.weight) / rhs.length;
//}
//
//class Edge {
//public:
//	Edge(int64_t f, int64_t s, int64_t l) : first(f), second(s), length(l) {}
//	int64_t first, second, length;
//};
//
//}
//
//int64_t scheduling1() {
//	std::multiset<SchedulingDiff> jobs;
//
//	std::ifstream input("jobs.txt");
//	if (!input.good() || !input.is_open()) {
//		std::cout << "badfile\n";
//	}
//	int64_t total;
//	input >> total;
//	while (input.good()) {
//		int64_t f, s;
//		input >> f;
//		input >> s;
//		jobs.insert(SchedulingDiff(f, s));
//	}
//
//	int64_t time = 0;
//	int64_t result = 0;
//	for (auto &item : jobs) {
//		time += item.length;
//		result += time * item.weight;
//	}
//	return result;
//}
//
//int64_t scheduling2() {
//	std::multiset<SchedulingRatio> jobs;
//
//	std::ifstream input("jobs.txt");
//	if (!input.good() || !input.is_open()) {
//		std::cout << "badfile\n";
//	}
//	int64_t total;
//	input >> total;
//	while (input.good()) {
//		int64_t f, s;
//		input >> f;
//		input >> s;
//		jobs.insert(SchedulingRatio(f, s));
//	}
//
//	int64_t time = 0;
//	int64_t result = 0;
//	for (auto &item : jobs) {
//		time += item.length;
//		result += time * item.weight;
//	}
//	return result;
//}
//
//int64_t mst() {
//	std::vector<Edge> edges;
//
//	std::ifstream input("edges.txt");
//	if (!input.good() || !input.is_open()) {
//		std::cout << "badfile\n";
//	}
//	int64_t totalv, totale;
//	input >> totalv;
//	input >> totale;
//	while (input.good()) {
//		int64_t f, s, l;
//		input >> f;
//		input >> s;
//		input >> l;
//		edges.emplace_back(f, s, l);
//	}
//
//	std::vector<bool> in(totalv + 1, false);
//	in[0] = in[1] = true;
//	int64_t result = 0;
//	for (int64_t i = 1; i < totalv; ++i) {
//		std::map<int64_t, int64_t> cross;
//		for (auto &edge : edges) {
//			if (in[edge.first] != in[edge.second]) {
//				cross[edge.length] = (in[edge.second]) ? edge.first : edge.second;
//			}
//		}
//		result += cross.begin()->first;
//		assert(in[cross.begin()->second] == false);
//		in[cross.begin()->second] = true;
//	}
//
//	for (auto &i : in) {
//		assert(i);
//	}
//
//	return result;
//}
//

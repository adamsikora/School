//#include "StlBase.h"
//#undef max
//
//int64_t knapsack_base() {
//	std::vector<std::pair<int64_t, int64_t>> items;
//
//	std::ifstream input("knapsack1.txt");
//	if (!input.good() || !input.is_open()) {
//		std::cout << "badfile\n";
//	}
//	int64_t total, totalitems;
//	input >> total;
//	input >> totalitems;
//	for (int i = 0; i < totalitems; ++i) {
//		int64_t f, s;
//		input >> f;
//		input >> s;
//		items.emplace_back(f, s);
//	}
//	std::vector<std::vector<int64_t>> A(totalitems + 1, std::vector<int64_t>(total + 1, 0));
//
//	for (int64_t i = 1; i <= totalitems; ++i) {
//		for (int64_t x = 0; x <= total; ++x) {
//			A[i][x] = std::max(A[i - 1][x], items[i - 1].second > x ? 0 : A[i - 1][x - items[i - 1].second] + items[i - 1].first);
//		}
//	}
//	return A[totalitems][total];
//}
//
//
//std::vector<std::pair<int64_t, int64_t>> items;
//int64_t total, totalitems;
//
//void initialize() {
//	std::ifstream input("knapsack_big.txt");
//	if (!input.good() || !input.is_open()) {
//		std::cout << "badfile\n";
//	}
//	input >> total;
//	input >> totalitems;
//	for (int i = 0; i < totalitems; ++i) {
//		int64_t f, s;
//		input >> f;
//		input >> s;
//		items.emplace_back(f, s);
//	}
//}
//
//std::unordered_map<int64_t, int64_t> A;
//
//int64_t recurse(int64_t i, int64_t x) {
//	assert(x <= total);
//	assert(i <= totalitems);
//	int64_t p = x * 1000000 + i;
//	if (A.count(p)) {
//		return A[p];
//	} else {
//		if (x == 0 || i == 0) {
//			A[p] = 0;
//			return 0;
//		}
//		int64_t result = std::max(recurse(i - 1, x), items[i - 1].second > x ? 0 : recurse(i - 1, x - items[i - 1].second) + items[i - 1].first);
//		A[p] = result;
//		return result;
//	}
//}
//
//int64_t knapsack() {
//	initialize();
//	return recurse(totalitems, total);
//}
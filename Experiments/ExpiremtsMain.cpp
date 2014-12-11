#include "StlBase.h"
#include "StopWatch.h"
#include "RandomUtils.h"
#include "Clipboard.h"
#include "MatlabEngine.h"
#include <unordered_set>

const int size = 10;
const int ntry = 10000;

std::vector<bool> propousti(size*size, false);

bool lij(double prob) {
	for (int i = 0; i < size*size; ++i) {
		propousti[i] = utils::random::decide(prob);
	}
	std::vector<bool> propRadek(size, false), propPredRadek(size, false), start(size, false);;
	for (int i = 0; i < size; ++i) {
		propRadek[i] = propousti[i];
	}
	for (int radek = 1; radek < size; ++radek) {
		propPredRadek = propRadek;
		propRadek = start;
		for (int i = 0; i < size; ++i) {
			propRadek[i] = propPredRadek[i] && propousti[radek*size + i];
		}
		for (int i = 0; i < size; ++i) {
			if (propRadek[i]) {
				int pos = i + 1;
				while (pos < size && propousti[radek*size + pos] && propRadek[pos] == false) {
					propRadek[pos] = true;
					++pos;
				}
				pos = i - 1;
				while (pos >= 0 && propousti[radek*size + pos] && propRadek[pos] == false) {
					propRadek[pos] = true;
					--pos;
				}
			}
		}
	}
	for (int i = 0; i < size; ++i) {
		if (propRadek[i]) {
			return true;
		}
	}
	return false;
}

int main() {
	utils::StopWatch sw(true);
	std::vector<std::pair<double, double>> res, results;
	for (double prob = 0.0; prob <= 1.0; prob += 0.01) {
		std::cout << prob << std::endl;
		int success = 0;
		for (int tries = 0; tries < ntry; ++tries) {
			if (lij(prob)) {
				++success;
			}
		}
		res.emplace_back(prob, double(success) / ntry);
	}
	//int start = -1, end = size;
	//while (res[++start].second == 0.0);
	//while (res[--end].second == 1.0);
	//for (int i = start; i <= end; ++i) {
	//	results.emplace_back(res[i]);
	//}
	utils::matlab::plot(res);
	sw.stop();
	std::cout << sw.getLastElapsed();
	std::cin.ignore();

  return 0;
}
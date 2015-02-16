#include "StlBase.h"
#include "MatlabEngine.h"

#include "Neighborhood.h"

namespace {

int count = 0;

void recurse(uint64_t position, const std::vector<uint64_t>& lattice, std::vector<int64_t>& counter) {
	for (int i = 0; i < 6; ++i) {
		int neigh = neigh::neigh(i, position);
		if (counter[neigh] == 0) {
			if (lattice[neigh] == 0) {
				counter[neigh] = -1;
			} else {
				counter[neigh] = count;
				recurse(neigh, lattice, counter);
			}
		}
	}
}

}

std::map<int64_t, int64_t> countClusters(const std::vector<uint64_t>& lattice) {
	count = 1;
	std::vector<int64_t> counter(lattice.size(), 0);
	for (int i = 0; i < lattice.size(); ++i) {
		if (counter[i] == 0) {
			if (lattice[i] == 0) {
				counter[i] = -1;
			} else {
				counter[i] = count;
				recurse(i, lattice, counter);
				++count;
			}
		}
	}
	std::vector<uint64_t> c(counter.size(), 0);
	for (int i = 0; i < lattice.size(); ++i) {
		c[i] = counter[i] + 1;
	}
	//utils::matlab::draw(c, std::pair<uint64_t, uint64_t>(c::w, c::h));
	std::vector<int64_t> islands(count, 0);
	for (int i = 0; i < counter.size(); ++i) {
		if (counter[i] > 0) ++islands[counter[i]];
	}
	std::map<int64_t, int64_t> result;
	for (auto island : islands) {
		if (result.count(island)) {
			++result[island];
		} else {
			result[island] = 1;
		}
	}
	return std::move(result);
}

double areaToVolume(const std::vector<uint64_t>& lattice) {
	int64_t area = 0, volume = 0;
	for (int64_t i = 0; i < lattice.size(); ++i) {
		if (lattice[i] != 0) {
			++volume;
			for (int j = 0; j < 6; ++j) {
				if (lattice[neigh::neigh(j, i)] == 0) {
					++area;
					break;
				}
			}
		}
	}
	return static_cast<double>(area) / volume;
}

double averageIsland(const std::vector<uint64_t>& lattice) {
	std::map<int64_t, int64_t> map = countClusters(lattice);
	if (map[1] > 1) --map[1];
	int64_t nIsl = 0, volume = 0;
	for (auto &isl : map) {
		nIsl += isl.second;
		volume += isl.first * isl.second;
	}
	return static_cast<double>(volume) / nIsl;
}
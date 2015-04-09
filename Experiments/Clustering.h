#include "StlBase.h"

namespace {

	class Edge {
	public:
		Edge(int64_t f, int64_t s, int64_t l) : first(f), second(s), length(l) {}
		int64_t first, second, length;
	};

	class UnionFind {
	public:
		UnionFind(int64_t nNodes) {
			nodes.reserve(nNodes);
			for (int64_t i = 0; i <= nNodes; ++i) {
				nodes.push_back(Node{ i, i, 1i64 });
			}
		}

		int64_t findParent(int64_t nodeIndex) {
			int64_t parent = nodes[nodeIndex].parent;
			if (parent == nodeIndex) {
				return parent;
			} else {
				int64_t result = findParent(parent);
				nodes[nodeIndex].parent = result;
				return result;
			}
		}

		void mergeNodes(int64_t first, int64_t second) {
			int64_t firstParent = findParent(first);
			int64_t secondParent = findParent(second);
			if (nodes[firstParent].size > nodes[secondParent].size) {
				nodes[firstParent].size += nodes[secondParent].size;
				nodes[secondParent].parent = firstParent;
			} else {
				nodes[secondParent].size += nodes[firstParent].size;
				nodes[firstParent].parent = secondParent;
			}
		}

		int64_t countClusters() {
			std::set<int64_t> cluster;
			for (uint64_t i = 1; i < nodes.size(); ++i) {
				cluster.insert(findParent(i));
			}
			return cluster.size();
		}

	private:
		struct Node {
			int64_t index, parent, size;
		};

		std::vector<Node> nodes;
	};
}

int64_t cluster1() {
	std::vector<Edge> edges;

	std::ifstream input("clustering1.txt");
	if (!input.good() || !input.is_open()) {
		std::cout << "badfile\n";
	}
	int64_t total;
	input >> total;
	while (input.good()) {
		int64_t f, s, l;
		input >> f;
		input >> s;
		input >> l;
		edges.push_back(Edge(f, s, l));
	}

	std::sort(edges.begin(), edges.end(), [](Edge first, Edge second) { return first.length < second.length; });

	UnionFind unionFind(total);

	int64_t toMerge = 500, length = 0;
	std::vector<Edge>::iterator it = edges.begin();
	while (toMerge > 4 && it != edges.end()) {
		if (unionFind.findParent(it->first) != unionFind.findParent(it->second)) {
			unionFind.mergeNodes(it->first, it->second);
			//std::cout << "Merged " << it->first << " and " << it->second << " with edge of length " << it->length << std::endl;
			--toMerge;
			length += it->length;
		}
		++it;
	}
	//std::cout << "Structure has " << unionFind.countClusters() << " clusters\n";

	while (unionFind.findParent(it->first) == unionFind.findParent(it->second)) ++it;

	return it->length;
}

int64_t cluster2() {
	std::vector<std::bitset<24>> vertices;

	std::ifstream input("clustering_big.txt");
	if (!input.good() || !input.is_open()) {
		std::cout << "badfile\n";
	}
	int64_t total, totalBits;
	input >> total;
	input >> totalBits;
	while (input.good()) {
		std::bitset<24> bs;
		for (int64_t i = 0; i < 24; ++i) {
			bool b;
			input >> b;
			bs[i] = b;
		}
		vertices.push_back(bs);
	}
	std::cout << "Loaded\n";

	UnionFind unionFind(total);

	for (int64_t i = 0; i < vertices.size(); ++i) {
		if (i % 1000 == 0) std::cout << i << std::endl;
		for (int64_t j = i + 1; j < vertices.size(); ++j) {
			int64_t count = 0;
			for (int64_t s = 0; s < 24; ++s) {
				if (vertices[i][s] != vertices[j][s]) {
					++count;
				}
			}
			if (count < 3) {
				int64_t first = unionFind.findParent(i + 1);
				int64_t second = unionFind.findParent(j + 1);
				if (first != second) {
					unionFind.mergeNodes(first, second);
				}
			}
		}
	}

	//int64_t toMerge = 500, length = 0;
	//std::vector<Edge>::iterator it = edges.begin();
	//while (toMerge > 4 && it != edges.end()) {
	//	if (unionFind.findParent(it->first) != unionFind.findParent(it->second)) {
	//		unionFind.mergeNodes(it->first, it->second);
	//		//std::cout << "Merged " << it->first << " and " << it->second << " with edge of length " << it->length << std::endl;
	//		--toMerge;
	//		length += it->length;
	//	}
	//	++it;
	//}
	////std::cout << "Structure has " << unionFind.countClusters() << " clusters\n";
	//
	//while (unionFind.findParent(it->first) == unionFind.findParent(it->second)) ++it;

	return unionFind.countClusters();
}
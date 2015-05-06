#include "StlBase.h"
#undef min
#undef max
#include "RandomUtils.h"

uint64_t size = 0;
std::vector<std::vector<uint64_t>> forward, backward;

std::vector<bool> visited;

std::vector<uint64_t> visitOrder;
std::vector<uint64_t> ordered;
std::vector<uint64_t> groupId;

uint64_t counter = size;

void visit(uint64_t vertex) {
	visited[vertex] = true;
	for (auto &next : backward[vertex]) {
		if (!visited[next]) {
			visit(next);
		}
	}
	visitOrder[vertex] = counter--;
}

void topologicalOrder() {
	counter = size;
	for (uint64_t i = 1; i <= size; ++i) {
		if (!visited[i]) {
			visit(i);
		}
	}
}

uint64_t id = 1;

void visitf(uint64_t vertex) {
	visited[vertex] = true;
	groupId[vertex] = id;
	for (auto &next : forward[vertex]) {
		if (!visited[next]) {
			visitf(next);
		}
	}
}

void scc() {
	id = 1;
	visited = std::vector<bool>(size + 1, false);
	for (uint64_t i = 1; i <= size; ++i) {
		if (!visited[ordered[i]]) {
			visitf(ordered[i]);
			++id;
		}
	}
}

std::string twosat() {
	std::stringstream ss;
	for (int in = 1; in < 7; ++in) {
		std::stringstream name;
		std::cout << name.str() << std::endl;
		name << "2sat" << in << ".txt";
		std::ifstream input(name.str());
		if (!input.good() || !input.is_open()) {
			std::cout << "badfile\n";
		}
		int64_t tot = 0;
		input >> tot;

		std::vector<std::pair<int64_t, int64_t>> clauses;
		clauses.reserve(tot);
		for (int64_t i = 0; i < tot; ++i) {
			int64_t f, s;
			input >> f;
			input >> s;
			clauses.emplace_back(f, s);
		}

		size = 2 * tot;
		forward = std::vector<std::vector<uint64_t>>(size + 1, std::vector<uint64_t>());
		backward = std::vector<std::vector<uint64_t>>(size + 1, std::vector<uint64_t>());

		visited = std::vector<bool>(size + 1, false);

		visitOrder = std::vector<uint64_t>(size + 1, 0);
		ordered = std::vector<uint64_t>(size + 1, 0);
		groupId = std::vector<uint64_t>(size + 1, 0);

		uint64_t counter = size;

		for (auto &clause : clauses) {
			int64_t first = (clause.first > 0) ? clause.first : -clause.first + tot;
			int64_t second = (clause.second > 0) ? clause.second : -clause.second + tot;
			int64_t notFirst = (clause.first < 0) ? -clause.first : clause.first + tot;
			int64_t notSecond = (clause.second < 0) ? -clause.second : clause.second + tot;
			forward[notFirst].push_back(second);
			forward[notSecond].push_back(first);
			backward[second].push_back(notFirst);
			backward[first].push_back(notSecond);
		}

		topologicalOrder();
		for (uint64_t i = 1; i <= size; ++i) {
			ordered[visitOrder[i]] = i;
		}
		scc();

		bool satisfiable = true;
		for (int64_t i = 1; i <= tot; ++i) {
			if (groupId[i] == groupId[i + tot]) {
				satisfiable = false;
				break;
			}
		}
		ss << satisfiable;
	}
	return ss.str();
}
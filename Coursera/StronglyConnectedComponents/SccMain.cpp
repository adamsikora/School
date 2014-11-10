#include "StlBase.h"
#include "StopWatch.h"
#include "Clipboard.h"

uint64_t size = 875714;
std::vector<std::vector<uint64_t>> forward(size + 1, std::vector<uint64_t>()), backward(size + 1, std::vector<uint64_t>());

std::vector<bool> visited(size + 1, false);

std::vector<uint64_t> visitOrder(size + 1, 0);
std::vector<uint64_t> ordered(size + 1, 0);
std::vector<uint64_t> groupId(size + 1, 0);

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

int main() {
  utils::StopWatch sw(true);

  std::vector<std::pair<uint64_t, uint64_t>> edges;// = { { 2, 1 }, { 1, 3 }, { 3, 2 }, { 2, 4 }, { 3, 5 }, { 4, 6 }, { 5, 6 }, { 6, 5 } };

  std::ifstream input("SCC.txt");
  if (!input.good() || !input.is_open()) {
    std::cout << "badfile\n";
  }
  while (input.good()) {
    uint64_t f, s;
    input >> f;
    input >> s;
    edges.emplace_back(f, s);
  }
  input.close();

  sw.stop();
  std::cout << "loading took: " << sw.getLastElapsed() << std::endl;
  sw.start();

  for (auto &edge : edges) {
    forward[edge.first].push_back(edge.second);
    backward[edge.second].push_back(edge.first);
  }
  topologicalOrder();
  for (uint64_t i = 1; i <= size; ++i) {
    ordered[visitOrder[i]] = i;
  }
  scc();
  std::vector<uint64_t> counts(id, 0);
  for (uint64_t i = 1; i <= size; ++i) {
    counts[groupId[i]] += 1;
  }
  std::sort(counts.begin(), counts.end());

  std::stringstream ss;
  for (uint64_t i = 1; i <= 5; ++i) {
    ss << counts[counts.size() - i];
    if (i < 5) {
      ss << ",";
    }
  }
  std::cout << ss.str();
  utils::CopyToClipboard(ss.str());
  sw.stop();
  std::cout << "putting into representation took: " << sw.getLastElapsed() << std::endl;
  std::cin.ignore();

  return 0;
}
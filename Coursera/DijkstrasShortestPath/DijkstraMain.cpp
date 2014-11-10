#include "StlBase.h"
#include "StopWatch.h"
#include "Clipboard.h"

const int nVertices = 200;

struct Edge {
  Edge(int f, int s, int l) : first(f), second(s), length(l) {}
  int first, second, length;
};

std::vector<Edge> edges;
std::vector<bool> consumed(nVertices + 1, false);
std::vector<int> distances(nVertices + 1, 1000000);

void loadEdges() {
  std::ifstream input("dijkstraData.txt");
  if (!input.good() || !input.is_open()) {
    std::cout << "badfile\n";
  }
  const uint64_t bufferSize = 1024;
  char buffer[bufferSize];
  uint64_t gridPosition = 0;

  while (input.getline(buffer, bufferSize)) {
    std::string line = buffer;
    std::stringstream ss;
    ss << line;
    int first = 0, second = 0, length = 0;
    ss >> first;
    while (!ss.eof()) {
      ss >> second;
      ss.ignore(1);
      ss >> length;
      if (!ss.eof()) {
        edges.emplace_back(first, second, length);
      }
    }
  }
}

void dijkstra() {
  consumed[1] = true;
  distances[1] = 0;
  for (int i = 1; i <= nVertices; ++i) {
    int nextToConsume = 0;
    int shortest = 100000000;
    for (auto &edge : edges) {  // dumb O(m*n) algorithm no need to implement efficiently for the assignment
      if (consumed[edge.first] && !consumed[edge.second]) {
        if (shortest > distances[edge.first] + edge.length) {
          shortest = distances[edge.first] + edge.length;
          nextToConsume = edge.second;
        }
      }
    }
    consumed[nextToConsume] = true;
    distances[nextToConsume] = shortest;
  }
}

int main() {
  utils::StopWatch sw(true);

  loadEdges();

  dijkstra();

  std::vector<int> desired = { 7, 37, 59, 82, 99, 115, 133, 165, 188, 197 };
  std::stringstream ss;
  for (auto &vertex : desired) {
    ss << distances[vertex];
    if (vertex != desired.back()) {
      ss << ",";
    }
  }
  std::cout << ss.str() << std::endl;
  utils::CopyToClipboard(ss.str());

  sw.stop();
  std::cout << sw.getLastElapsed() << std::endl;
  std::cin.ignore();
  return 0;
}
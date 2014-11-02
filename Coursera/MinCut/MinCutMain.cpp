#include "StlBase.h"
#include "StopWatch.h"
#include "Clipboard.h"

std::mt19937 mt;

int findCut(std::list<std::pair<int, int>> edges) {
  for (int i = 200; i > 2; --i) {
    int cut = mt() % edges.size();
    auto it = edges.begin();
    for (int j = 0; j < cut; ++j, ++it) {}
    int first = it->first, second = it->second;
    edges.erase(it);
    for (auto jt = edges.begin(); jt != edges.end();) {
      if (jt->first == first) {
        if (jt->second == second) {
          auto toDel = jt++;
          edges.erase(toDel);
          continue;
        } else {
          jt->first = second;
        }
      } else if (jt->second == first) {
        if (jt->first == second) {
          auto toDel = jt++;
          edges.erase(toDel);
          continue;
        } else {
          jt->second = second;
        }
      }
      ++jt;
    }
  }
  return edges.size();
}

int main() {
  utils::StopWatch sw(true);

  std::ifstream input("kargerMinCut.txt");
  if (!input.is_open()) {
    std::cout << "failed to read file\n";
  }

  const uint64_t bufferSize = 4*1024;
  char buffer[bufferSize];

  std::vector<std::pair<int, std::vector<int>>> adjacency;
  while (input.getline(buffer, bufferSize)) {
    std::stringstream ss;
    ss << buffer;
    int first;
    ss >> first;
    std::vector<int> connections;
    while (!ss.eof()) {
      int i = 0;
      ss >> i;
      if (i != 0) {
        connections.push_back(i);
      }
    }
    adjacency.emplace_back(first, connections);
    //std::cout << ss.str() << std::endl;
  }
  std::list<std::pair<int, int>> edges;
  int edgecount = 0;
  for (auto &adj : adjacency) {
    edgecount += adj.second.size();
    for (auto second : adj.second) {
      if (adj.first < second) {
        edges.emplace_back(adj.first, second);
      }
    }
  }
  if (edgecount != 2 * edges.size()) {
    std::cout << "wrong input\n";
  }

  int best = edges.size();
  for (int i = 0; i < 200 * 200; ++i) {
    int next = findCut(edges);
    //std::cout << i << " " << next << std::endl;
    if (best > next) {
      best = next;
    }
  }
  std::stringstream bestStr;
  bestStr << best;
  utils::CopyToClipboard(bestStr.str());
  std::cout << bestStr.str() << std::endl;
  sw.stop();
  std::cout << sw.getLastElapsed() << std::endl;

  std::cin.ignore();
  return 0;
}
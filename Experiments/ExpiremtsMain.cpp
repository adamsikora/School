#include "StlBase.h"
#include "StopWatch.h"
#include "Clipboard.h"
#include "MatlabEngine.h"
#include <unordered_set>

int main() {
  std::ifstream file("Median.txt", std::ios_base::in);
  if (!file.good() || !file.is_open()) {
    std::cout << "badfile\n";
  }
  std::vector<int64_t> ints;
  while (file.good()) {
    int64_t next;
    file >> next;
    ints.push_back(next);
  }
  ints.pop_back();

  std::vector<int64_t> sorted;
  sorted.reserve(ints.size());

  int64_t answ = 0;

  for (auto it : ints) {
    auto sit = sorted.begin();
    while (*sit < it && sit != sorted.end()) {
      ++sit;
    }
    sorted.emplace(sit, it);
    answ += sorted[(sorted.size() - 1) / 2];
    answ %= 10000;
  }

  std::stringstream ss;
  ss << answ;

  std::cout << ss.str() << std::endl;
  utils::CopyToClipboard(ss.str());
  std::cin.ignore();

  return 0;
}

/*int main() {
  std::ifstream file("algo1-programming_prob-2sum.txt", std::ios_base::in);
  if (!file.good() || !file.is_open()) {
    std::cout << "badfile\n";
  }
  std::vector<int64_t> ints;
  while (file.good()) {
    int64_t next;
    file >> next;
    ints.push_back(next);
  }
  ints.pop_back();
  std::unordered_set<int64_t> hash;
  hash.reserve(1000000);
  for (auto it : ints) {
    hash.insert(it);
  }
  int64_t answ = 0, count = 0;
  std::vector<bool> is(20001, false);
  for (auto it : hash) {
    ++count;
    if (count % 1000 == 0) {
      std::cout << count << std::endl;
    }
    for (int64_t i = -10000; i <= 10000; ++i) {
      if (2 * it != i && hash.count(i - it)) {
        is[i+10000] = true;
      }
    }
  }
  for (auto it : is) {
    if (it) {
      ++answ;
    }
  }

  std::stringstream ss;
  ss << answ;

  std::cout << ss.str() << std::endl;
  utils::CopyToClipboard(ss.str());
  std::cin.ignore();

  return 0;
}*/
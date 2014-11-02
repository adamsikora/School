#include "StlBase.h"
#include "StopWatch.h"
#include "RandomUtils.h"

int main() {
  utils::random::Generator gen(2);
  std::cout << 1.0 - (static_cast<double>(std::numeric_limits<uint64_t>::max())) / (static_cast<double>(std::numeric_limits<uint64_t>::max()) + 1.0) << std::endl;

  std::cin.ignore();

  return 0;
}
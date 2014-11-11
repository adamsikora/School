#include "StlBase.h"
#include "StopWatch.h"
#include "MatlabEngine.h"

int main() {
  std::vector<std::pair<double, double>> vec;
  for (double x = -5; x <= 5; x += 0.1) {
    vec.emplace_back(x, sin(x));
  }
  utils::matlab::plot(vec);

  std::cin.ignore();
  return 0;
}
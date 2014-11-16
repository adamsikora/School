#include "StlBase.h"
#include "StopWatch.h"
#include "MatlabEngine.h"

const double A0 = 1e10;
const double k = 1e-7;
const double step = 1e-8;

int main() {
  std::vector<std::pair<double, double>> vec, topl;
  //for (double x = -5; x <= 5; x += 0.1) {
  //  vec.emplace_back(x, sin(x));
  //}
  //utils::matlab::plot(vec);
  
  vec.emplace_back(0.0, A0); topl.emplace_back(0.0, 0.0);
  /*for (double t = step; t < 0.1; t += step) {
    double trueValue = 1.0 / (1.0 / A0 + k*t);
    double newValue = vec.back().second - step*k*pow(vec.back().second, 2);
    vec.emplace_back(t, newValue);
    topl.emplace_back(t, (trueValue - newValue) / newValue);
  }*/
  for (double t = step; t < 0.1; t += step) {
	double trueValue = 1.0 / (1.0 / A0 + k*t);
	double oldValue = vec.back().second;
	double d1 = -step * k*pow(oldValue, 2);
	double d2 = -step * k*pow(oldValue + d1 / 2.0, 2);
	double d3 = -step * k*pow(oldValue + d2 / 2.0, 2);
	double d4 = -step * k*pow(oldValue + d3, 2);
	double newValue = oldValue + (d1+2*d2+2*d3+d3)/6.0;
	vec.emplace_back(t, newValue);
	topl.emplace_back(t, (trueValue - newValue) / newValue);
  }
	  utils::matlab::plot(topl);
  std::cin.ignore();

  return 0;
}
#include "StlBase.h"
#include "StopWatch.h"
#include "RandomUtils.h"
#include "Clipboard.h"
#include "MatlabEngine.h"
#include "JMol.h"
#include <unordered_set>

double normalDist(double x0, double sigma, double x) {
	return exp(-pow(x - x0, 2) / (2 * sigma*sigma)) / sqrt(2*3.14) / sigma;
}
double distr(double x) {
	return 0.3*normalDist(0.1, 0.1, x) + 0.7*normalDist(0.5, 0.07, x);
}

void checkPlot() {
	const int nrolls = 1000000;  // number of experiments

	std::default_random_engine generator;
	std::normal_distribution<double> distribution1(0.1, 0.1);
	std::normal_distribution<double> distribution2(0.5, 0.07);

	const double step = 0.01;

	std::vector<std::pair<double, double>> result;
	for (double d = 0; d < 1.0; d += step) {
		result.emplace_back(d, 0.0);
	}

	for (int i = 0; i < nrolls; ++i) {
		double number = utils::random::decide(0.3) ? distribution1(generator) : distribution2(generator);
		if (int(number / step) >= 0 && int(number / step) < result.size()) {
			result[int(number / step)].second += 1;
		}
	}

	utils::matlab::plot(result);
}

void metropolis() {
	const int nrolls = 1000000;
	double x = 0.5;

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 0.5);

	const double step = 0.01;

	std::vector<std::pair<double, double>> result;
	for (double d = 0; d < 1.0; d += step) {
		result.emplace_back(d, 0.0);
	}

	for (int i = 0; i < nrolls; ++i) {
		double newx = 0;
		while (true) {
			newx = x + distribution(generator);
			double oldp = distr(x);
			double newp = distr(newx);

			if (oldp < newp || utils::random::decide(newp / oldp)) {
				if (int(newx / step) >= 0 && int(newx / step) < result.size()) {
					result[int(newx / step)].second += 1;
				}
				break;
			}
		}
		x = newx;
	}
	utils::matlab::plot(result);
}

double getValue(double x) {
	return x*x - cos(20*(pow(cos(4*x), 8) - 1));
}

void greedy() {
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 0.5);
	double x = 2.0;
	while (true) {
		double newx = x + distribution(generator);
		if (getValue(newx) < getValue(x)) {
			x = newx;
			std::cout << x << std::endl;
		}
	}
}

int main() {
	utils::StopWatch sw(true);

	//metropolis();

	//checkPlot();

	//std::vector<std::pair<double, double>> result;
	//for (double x = -1.0; x <= 1.0; x += 0.01) {
	//	result.emplace_back(x, getValue(x));
	//}
	//utils::matlab::plot(result);

	greedy();

	sw.stop();
	std::cout << sw.getLastElapsed();
	std::cin.ignore();

	return 0;
}
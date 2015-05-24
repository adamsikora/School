

#include "StlBase.h"
#include "MatlabEngine.h"
#include "StopWatch.h"
#include "RandomUtils.h"

#include "DynamicTsp.h"
#include "KohonenMapTsp.h"

#define REPORT

const int64_t totalVertices = 100;

int main() {
	utils::matlab::DataVector data;
	utils::random::Generator gen(20);
	for (int64_t i = 0; i < totalVertices; ++i) {
		data.emplace_back(gen.get01(), gen.get01());
	}
	//utils::matlab::plot(data);

	utils::StopWatch sw(true);

	DynamicTsp dynSalesman(data);

	//std::cout << "Shortest path is: " << dynSalesman.findShortestPath() << std::endl;
	sw.stop();
	std::cout << sw.getLastElapsed() << std::endl;

	for (int64_t i = 0; i < 10; ++i) {
		sw.start();
		KohonenMapTsp kohonenSalesman(data, i);
		std::cout << "Shortest kohonen path is: " << kohonenSalesman.findShortestPath() << std::endl;
		sw.stop();
		std::cout << sw.getLastElapsed() << std::endl;
	}
	//utils::CopyToClipboard(ss.str());
	std::cin.ignore();

	return 0;
}
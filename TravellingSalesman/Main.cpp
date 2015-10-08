

#include "StlBase.h"
#include "MatlabEngine.h"
#include "StopWatch.h"
#include "RandomUtils.h"

#include "DynamicTsp.h"
#include "KohonenMapTsp.h"
#include "SimulatedAnnealingTsp.h"
#include "AntColonyTsp.h"

#define REPORT

const int64_t totalVertices = 50;

int main() {
	std::string outFile = "tspx.txt";
	remove(outFile.c_str());
	freopen(outFile.c_str(), "w", stdout);
	utils::matlab::DataVector data;
	utils::random::Generator gen(25);
	for (int64_t i = 0; i < totalVertices; ++i) {
		data.emplace_back(gen.get01(), gen.get01());
	}
	//utils::matlab::plot(data);

	utils::StopWatch sw(true);

	std::cout << "Solution of traveling salesman problem for " << totalVertices << " randomly generated points" << std::endl << std::endl;

	//DynamicTsp dynSalesman(data);
	//std::cout << "Shortest path calculated with dynamic method (exact) is: " << dynSalesman.findShortestPath() << std::endl;
	//sw.stop();
	//std::cout << "calculation took: " << sw.getLastElapsed() << std::endl << std::endl;
	//
	//sw.start();
	//KohonenMapTsp kohonenSalesman(data, 1);
	//std::cout << "Shortest path calculated through use of Kohonen maps is: " << kohonenSalesman.findShortestPath() << std::endl;
	//sw.stop();
	//std::cout << "calculation took: " << sw.getLastElapsed() << std::endl << std::endl;
	//
	//sw.start();
	//SimulatedAnnealingTsp annealingSalesman(data, 1);
	//std::cout << "Shortest path calculated through use of simulated annealing is: " << annealingSalesman.findShortestPath() << std::endl;
	//sw.stop();
	//std::cout << "calculation took: " << sw.getLastElapsed() << std::endl << std::endl;
	//
	sw.start();
	AntColonyTsp antSalesman(data, 1);
	std::cout << "Shortest path calculated through use of ant colony optimization is: " << antSalesman.findShortestPath() << std::endl;
	sw.stop();
	std::cout << "calculation took: " << sw.getLastElapsed() << std::endl << std::endl;
	//utils::CopyToClipboard(ss.str());
	std::cin.ignore();

	return 0;
}
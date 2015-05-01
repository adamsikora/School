

#include "StlBase.h"
#include "MatlabEngine.h"
#include "StopWatch.h"

#include "DynamicTsp.h"

int main() {
	utils::matlab::DataVector data;
	data.emplace_back(0, 0);
	data.emplace_back(0, 1);
	data.emplace_back(1, 0);
	data.emplace_back(1, 1);
	//utils::matlab::plot(data);

	utils::StopWatch sw(true);

	DynamicTsp salesman(data);

	std::stringstream ss;
	ss << salesman.findShortestPath();
	std::cout << "Shortest path is: " << ss.str() << std::endl;
	//utils::CopyToClipboard(ss.str());

	sw.stop();
	std::cout << sw.getLastElapsed();
	std::cin.ignore();

	return 0;
}
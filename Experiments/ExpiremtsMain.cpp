#include "StlBase.h"
#include "StopWatch.h"
#include "RandomUtils.h"
#include "Clipboard.h"
#include "MatlabEngine.h"
#include "FileUtils.h"
#include <unordered_set>

#include "SchedulingAndMst.h"
#include "Clustering.h"
#include "Knapsack.h"
#include "AllPiarsShortestPaths.h"
#include "Tsp.h"
#include "2sat.h"

int main() { 
	utils::StopWatch sw(true);

	std::stringstream ss;
	ss << twosat();
	std::cout << ss.str() << std::endl;
	utils::CopyToClipboard(ss.str());

	sw.stop();
	std::cout << sw.getLastElapsed();
	std::cin.ignore();
 
  return 0;
}
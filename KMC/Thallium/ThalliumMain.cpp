

#include "Events.h"
#include "StopWatch.h"
#include "State.h"
#include "ClusterCount.h"

int main()
{
	utils::StopWatch sw;
	sw.start();

	std::ofstream file("out.txt");

	State state("startstate2");
	for (double T = 50; T <= 500; T += 50) {
		state.setParameter("T", T);
		Events events(state);
		State end = events.growthSimulation();
		file << T << "\t" << areaToVolume(end.getLattice()) << "\t" << averageIsland(end.getLattice()) << "\n";
		std::cout << T << "\t" << areaToVolume(end.getLattice()) << "\t" << averageIsland(end.getLattice()) << "\n";
	}
	file.close();
	//Events events(state);
	//State end = events.growthSimulation();
	//auto res = countClusters(end.getLattice());
	//std::cout << areaToVolume(end.getLattice()) << std::endl;
	//std::cout << averageIsland(end.getLattice()) << std::endl;

	//std::vector<uint64_t> vec(c::A, 0);
	//for (int i = -2; i <= 2; ++i) {
	//	vec[c::A / 2 + c::w / 4 + i] = 1;
	//	vec[c::A / 2 + c::w / 4 + c::w * i] = 1;
	//	vec[c::A / 2 + c::w / 4 + c::w * i - i] = 1;
	//}
	//State s(Parameters(), Results(), vec);
	//Reporter r(s);
	//r.pdbPut(s, "star");

	sw.stop();
	std::cout << "Simulation completed, it took: " << sw.getTotalElapsed() << "\n";

	std::cin.ignore();

	return 0;
}
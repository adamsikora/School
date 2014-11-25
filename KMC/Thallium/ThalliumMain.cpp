

#include "Events.h"
#include "StopWatch.h"
#include "State.h"

int main()
{
	utils::StopWatch sw;
	sw.start();

	State state("startstate2");
	Events events(state);
	events.growthSimulation();

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
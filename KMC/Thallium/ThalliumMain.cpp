

#include "Events.h"
#include "StopWatch.h"
#include "State.h"

int main()
{
	utils::StopWatch sw;
	sw.start();

	State state("startstate");
   Events events(state);
   events.growthSimulation();

	//std::vector<uint64_t> v(c::A, 0);
	//v[2] = v[3] = 1;
	//Parameters paras;
	//paras.set("newPara", 1.0);
	//paras.set("boltz", c::boltzmann);
	//Results res;
	//res.set("newPara", 5641.0);
	//
	//State state(paras, res, v);
	//state.saveState("newstate");
	//State nexts("newstate");
	//nexts.saveState("nextstate");

	sw.stop();
	std::cout << "Simulation completed, it took: " << sw.getTotalElapsed() << "\n";

	std::cin.ignore();

	return 0;
}
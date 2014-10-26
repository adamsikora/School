#include "Input.h"
#include "Events.h"
#include "StopWatch.h"
#include "State.h"

int main()
{
	utils::StopWatch sw;
	sw.start();

   //Parameters pomPara(inputPara);
	//
   //std::cout << pomPara.getAll();
	//
   //Report report(pomPara);
	//
   //Events events(report);
   //events.growthSimulation();
	//
   //report.saveIt("");
   //
   //std::cout << report.results.getHeadRow() << std::endl;
   //std::cout << report.results.getAllRows() << std::endl << std::endl;
   //std::cout << "\n\n\n";

	std::vector<uint64_t> v(c::A, 0);
	v[2] = v[3] = 1;
	next::Parameters paras;
	paras.set("newPara", 1.0);
	paras.set("boltz", c::boltzmann);
	next::Results res;
	res.set("newPara", 5641.0);

	State state(paras, res, v);
	state.saveState("newstate");
	State nexts("newstate");
	nexts.saveState("nextstate");

	sw.stop();
	std::cout << "Simulation completed, it took: " << sw.getTotalElapsed() << "\n";

	std::cin.ignore();

	return 0;
}
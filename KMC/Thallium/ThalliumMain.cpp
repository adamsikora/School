

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

	sw.stop();
	std::cout << "Simulation completed, it took: " << sw.getTotalElapsed() << "\n";

	std::cin.ignore();

	return 0;
}
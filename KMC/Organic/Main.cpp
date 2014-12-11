/*
Adam Sikora
11.9.2013

*/

#include "Events.h"
#include "StopWatch.h"

int main()
{
  utils::StopWatch sw;
	sw.start();

	Events events;
   events.simulation(50.0, 20);
	/*int poc = 25000000;
	while (poc--) {
		events.execute();
	}
	Output::pdbput(events.getMolec(), "01");*/
	/*events.noDep();
	poc = 10000000;
	while (poc--) {
		events.execute();
	}
	Output::pdbput(events.getMolec(), "02");*/
	sw.stop();
	events.report();
	events.crossCheck();
	std::cout << std::endl << "simulation time: " << sw.getLastElapsed() << std::endl;

	std::cin.ignore();
	return EXIT_SUCCESS;
}

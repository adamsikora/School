/*

*/

#ifndef EVENTS_H
#define EVENTS_H

#include "Includes.h"

#include "EventList.h"
#include "Rates.h"
#include "Grid.h"
#include "Output.h"

class Events
{
public:
   Events() : _nEvents(0), _nAds(0), _nDiff(0), _nRot(0), _time(0.0), _depoTime(0.0), _relaxTime(0.0), rates(), grid(), eventLists(grid._molecules)
	{
		_random.seed(c::seed); _trandom.seed(c::seed + 2);
		rates._setRates();
	}

	double getTime() const { return _time; }
	int getnDiff() const { return _nDiff; }
	int getnRot() const { return _nRot; }
   int getnEvents() const { return _nAds + _nDiff + _nRot; }
   double getCoverage() const { return static_cast<double>(grid._molecules.size() * Molecule(1, Coord(0, 0), 0).getA()) / c::A; }

	void execute();
   void simulation(double depositionTime, double relaxationTime = 0.0);

	void report();
	void crossCheck();

	std::vector<Molecule>& getMolec() { return grid._molecules; }
	void noDep() { rates._ads = 0.0; }

private:
	int _nEvents, _nAds, _nDiff, _nRot;
	double _time, _depoTime, _relaxTime;

	Rates rates;
	Grid grid;
	EventLists eventLists;

	MTRand _random;
	MTRand_open _trandom;

	void alterEvents(int posinMolList);

};

extern Events events;


#endif //EVENTS_H
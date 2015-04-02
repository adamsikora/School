#pragma once

#include "RandomUtils.h"

#include "Lattice.h"
#include "Rates.h"
#include "EventList.h"

class Events {
	struct Properties {
		int64_t nEvents, nAds, nDiff, nRot;
		double time;
	};
public:
	Events() : lattice(), rates(), eventLists(lattice.moleculeVector()), _random(c::seed) {};

	void simulation();

private:
	void execute();
	void alterEvents(int64_t posinMolList);

	void crossCheck();

	Lattice lattice;
	Rates rates;
	EventLists eventLists;
	Properties properties;

	utils::random::Generator _random;

};
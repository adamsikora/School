#pragma once

#include "RandomUtils.h"

#include "Lattice.h"
#include "Rates.h"
#include "EventList.h"

class Events {
	struct Properties {
		int64_t nEvents, nAds, nDiff, nRot;
		double time;
		std::string show() {
			std::stringstream ss;
			ss << nEvents << "\t" << nAds << "\t" << nDiff << "\t" << nRot << "\t" << time << "\n";
			return ss.str();
		}
		std::string showHead() { return "events\tads\tdiff\trot\ttime\n"; }
	};
public:
	Events() : lattice(), rates(), eventLists(lattice.moleculeVector()), _random(c::seed) {};

	void simulation();

private:
	void execute();
	void alterEvents(int64_t posinMolList);

	int64_t crossCheck(bool correctResultsReporting = false);

	Lattice lattice;
	Rates rates;
	EventLists eventLists;
	Properties properties;

	utils::random::Generator _random;

};
#pragma once

#include "RandomUtils.h"

#include "Lattice.h"
#include "Rates.h"
#include "EventList.h"

class Events {
	struct Properties {
		int64_t nEvents, nAds, nDiff;
		double time;
		std::string show() {
			std::stringstream ss;
			ss << nEvents << "\t" << nAds << "\t" << nDiff << "\t" << time << "\n";
			return ss.str();
		}
		std::string showHead() { return "events\tads\tdiff\ttime\n"; }
	};
public:
	Events(double Ed = c::E_d) : E_d(Ed),  lattice(), rates(Ed), eventLists(lattice), _random(c::seed){};

	void simulation();

private:
	void execute();
	void alterEvents(Position pos);

	bool molDescent(Position& pos);

	void countBounds();

	int64_t crossCheck(bool correctResultsReporting = false);

	double E_d;
	Lattice lattice;
	Rates rates;
	EventLists eventLists;
	Properties properties;

	utils::random::Generator _random;

};
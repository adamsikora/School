#pragma once

#include "BaseClass.h"
#include "Lattice.h"

class Events;

class EventLists {
public:
	EventLists(Lattice& reftogrid) : lattice(reftogrid) {}

	friend class Events;

	void properDiffEventReplace(GridCell& molecule, Diffusion shift, int64_t oldBounds);

	void properDiffEventAddition(Position pos, Diffusion shift, int64_t newBounds);

private:
	Lattice& lattice;

	std::vector<DiffusionEvent> _diffEvents[c::maxBoundCount];

};
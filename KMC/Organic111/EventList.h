#pragma once

#include "Molecule.h"

class Events;

class EventLists {
public:
	EventLists(std::vector<Molecule>& reftoMol) : molecules(reftoMol) {}

	friend class Events;

	void properDiffEventReplace(int64_t posinMolList, Diffusion shift, int64_t oldBounds);
	void properRotEventReplace(int64_t posinMolList, Rotation rot, int64_t oldBounds);

	void properDiffEventAddition(int64_t posinMolList, Diffusion shift, int64_t newBounds);
	void properRotEventAddition(int64_t posinMolList, Rotation rot, int64_t newBounds);

private:
	std::vector<Molecule>& molecules;

	std::vector<DiffusionEvent> _diffEvents[c::maxBoundCount];
	std::vector<RotationEvent> _rotEvents[c::maxBoundCount];

};
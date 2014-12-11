#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "Includes.h"
#include "Grid.h"

class Events;

class EventLists
{
public:
	EventLists(std::vector<Molecule>& reftoMol) : molecules(reftoMol) {}

	friend class Events;

	void properDiffEventReplace(int posinMolList, int shift, int oldBounds);
	void properRotEventReplace(int posinMolList, int rot, int oldBounds);

	void properDiffEventAddition(int posinMolList, int shift, int newBounds);
	void properRotEventAddition(int posinMolList, int rot, int newBounds);

private:
	std::vector<Molecule>& molecules;

	std::vector<MoleculeDiffEvent> _diffEvents[c::maxBoundCount];
	std::vector<MoleculeRotEvent> _rotEvents[c::maxBoundCount];

};

#endif //EVENTLIST_H
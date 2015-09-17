#include "EventList.h"

void EventLists::properDiffEventReplace(GridCell& molecule, Diffusion shift, int64_t oldBounds) {
	int64_t posinEventList = molecule.diffEvent(shift);
	molecule.setDiffEvent(shift, c::empty);
	if (posinEventList < static_cast<int64_t>(_diffEvents[oldBounds].size() - 1)) {
		_diffEvents[oldBounds][posinEventList] = _diffEvents[oldBounds].back();
		lattice[_diffEvents[oldBounds][posinEventList].moleculePos].setDiffEvent(_diffEvents[oldBounds][posinEventList].movement, posinEventList);
	}
	_diffEvents[oldBounds].pop_back();
}

void EventLists::properDiffEventAddition(Position pos, Diffusion shift, int64_t newBounds) {
	_diffEvents[newBounds].emplace_back(pos, shift);
	lattice[pos].setDiffEvent(shift, _diffEvents[newBounds].size() - 1);
}
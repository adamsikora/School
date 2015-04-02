#include "EventList.h"

void EventLists::properDiffEventReplace(int64_t posinMolList, Diffusion shift, int64_t oldBounds) {
	int64_t posinEventList = molecules[posinMolList].diffEvent(shift);
	molecules[posinMolList].setDiffEvent(shift, c::empty);
	if (posinEventList < static_cast<int64_t>(_diffEvents[oldBounds].size() - 1)) {
		_diffEvents[oldBounds][posinEventList] = _diffEvents[oldBounds].back();
		molecules[_diffEvents[oldBounds][posinEventList].molecule].setDiffEvent(_diffEvents[oldBounds][posinEventList].movement, posinEventList);
	}
	_diffEvents[oldBounds].pop_back();
}

void EventLists::properRotEventReplace(int64_t posinMolList, Rotation rot, int64_t oldBounds) {
	int64_t posinEventList = molecules[posinMolList].rotEvent(rot);
	molecules[posinMolList].setRotEvent(rot, c::empty);
	if (posinEventList < static_cast<int64_t>(_rotEvents[oldBounds].size() - 1)) {
		_rotEvents[oldBounds][posinEventList] = _rotEvents[oldBounds].back();
		molecules[_rotEvents[oldBounds][posinEventList].molecule].setRotEvent(_rotEvents[oldBounds][posinEventList].rotation, posinEventList);
	}
	_rotEvents[oldBounds].pop_back();
}


void EventLists::properDiffEventAddition(int64_t posinMolList, Diffusion shift, int64_t newBounds) {
	_diffEvents[newBounds].emplace_back(posinMolList, shift);
	molecules[posinMolList].setDiffEvent(shift, _diffEvents[newBounds].size() - 1);
}

void EventLists::properRotEventAddition(int64_t posinMolList, Rotation rot, int64_t newBounds) {
	_rotEvents[newBounds].emplace_back(posinMolList, rot);
	molecules[posinMolList].setRotEvent(rot, _rotEvents[newBounds].size() - 1);
}
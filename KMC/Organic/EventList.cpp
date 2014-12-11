#include "EventList.h"

void EventLists::properDiffEventReplace(int posinMolList, int shift, int oldBounds)
{
	unsigned posinEventList = molecules[posinMolList].getDiffEventPoint(shift);
	molecules[posinMolList].setDiffEventPoint(shift, c::empty);
	if (posinEventList < _diffEvents[oldBounds].size() - 1) {
		_diffEvents[oldBounds][posinEventList] = _diffEvents[oldBounds].back();
		molecules[_diffEvents[oldBounds][posinEventList].iMol].setDiffEventPoint(_diffEvents[oldBounds][posinEventList].shift, posinEventList);
	}
	_diffEvents[oldBounds].pop_back();
}

void EventLists::properRotEventReplace(int posinMolList, int rot, int oldBounds)
{
	unsigned posinEventList = molecules[posinMolList].getRotEventPoint(rot);
	molecules[posinMolList].setRotEventPoint(rot, c::empty);
	if (posinEventList < _rotEvents[oldBounds].size() - 1) {
		_rotEvents[oldBounds][posinEventList] = _rotEvents[oldBounds].back();
		molecules[_rotEvents[oldBounds][posinEventList].iMol].setRotEventPoint(_rotEvents[oldBounds][posinEventList].rot, posinEventList);
	}
	_rotEvents[oldBounds].pop_back();
}


void EventLists::properDiffEventAddition(int posinMolList, int shift, int newBounds)
{
	_diffEvents[newBounds].emplace_back(shift, posinMolList);
	molecules[posinMolList].setDiffEventPoint(shift, _diffEvents[newBounds].size() - 1);
}

void EventLists::properRotEventAddition(int posinMolList, int rot, int newBounds)
{
	_rotEvents[newBounds].emplace_back(rot, posinMolList);
	molecules[posinMolList].setRotEventPoint(rot, _rotEvents[newBounds].size() - 1);
}
#include "Events.h"

void Events::simulation() {
	while (properties.time < c::finalTime) {
		execute();
	}
}

void Events::execute() {
	rates._setSums(eventLists._diffEvents, eventLists._rotEvents);

	properties.time -= log(_random.get01()) / rates._total;

startOver:

	double chooseEvent = (rates._totalAds + rates._totalDiff + rates._totalRot) * _random.get01();

	if (chooseEvent < rates._totalAds) {
		int pom = static_cast<int> ((chooseEvent / rates._totalAds) * c::A * c::nRotations);
		Position pomPos(pom % c::h, pom / c::nRotations / c::h);
		Rotation pomRot = static_cast<Rotation>(pom / c::A);
		Molecule pomMol(pomPos, pomRot, phthalocyanine);

		if (lattice.molDescent(pomMol))
			alterEvents(lattice.addMolecule(pomMol)),
			properties.nAds++, properties.nEvents++;
		else
			goto startOver;
	}
	 else if (chooseEvent < rates._totalAds + rates._totalRot) {
	 chooseEvent -= rates._totalAds;
	 double cumulateRates = 0;
	 int ei = 0, ej = 0;
	 while (cumulateRates + rates._sumsofRot[ei] < chooseEvent)
	 cumulateRates += rates._sumsofRot[ei++];
	 ej = static_cast<int> (floor((chooseEvent - cumulateRates) / rates._rot[ei]));

	 alterEvents(lattice.rotateMolecule(eventLists._rotEvents[ei][ej]));
	 properties.nRot++, properties.nEvents++;
	 }
	else {
		chooseEvent -= rates._totalAds + rates._totalRot;
		double cumulateRates = 0;
		int ei = 0, ej = 0;
		while (cumulateRates + rates._sumsofDiff[ei] < chooseEvent)
			cumulateRates += rates._sumsofDiff[ei++];
		ej = static_cast<int> (floor((chooseEvent - cumulateRates) / rates._diff[ei]));

		alterEvents(lattice.moveMolecule(eventLists._diffEvents[ei][ej]));
		properties.nDiff++, properties.nEvents++;
	}
}

void Events::alterEvents(int64_t posinMolList) {
	std::set<int64_t> toAlter = lattice.getSetToAlter(posinMolList);

	for (std::set<int64_t>::iterator it = toAlter.begin(); it != toAlter.end(); it++) {

		/*int oldBounds = lattice._molecules[*it].getBounds();
		lattice.boundCount(lattice._molecules[*it]);
		int newBounds = lattice._molecules[*it].getBounds();

		if (newBounds != oldBounds) {
			for (int i = 0; i < 4; i++)
				if (grid._molecules[*it].getDiffEventPoint(i) != c::empty)
					eventLists.properDiffEventReplace(*it, i, oldBounds);
			for (int i = 0; i < 2; i++)
				if (grid._molecules[*it].getRotEventPoint(i) != c::empty)
					eventLists.properRotEventReplace(*it, i, oldBounds);
		}

		for (int i = 0; i < 4; i++)
			if (grid._molecules[*it].getDiffEventPoint(i) == c::empty)
				if (grid.isMoveFree(*it, i))
					eventLists.properDiffEventAddition(*it, i, newBounds);
				else;
			else
				if (!grid.isMoveFree(*it, i))
					eventLists.properDiffEventReplace(*it, i, oldBounds);

		for (int i = 0; i < 2; i++)
			if (grid._molecules[*it].getRotEventPoint(i) == c::empty)
				if (grid.isRotFree(*it, i))
					eventLists.properRotEventAddition(*it, i, newBounds);
				else;
			else
				if (!grid.isRotFree(*it, i))
					eventLists.properRotEventReplace(*it, i, oldBounds);*/
	}
}
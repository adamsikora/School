
#include "FileUtils.h"

#include "Events.h"

void Events::simulation() {
	bool hasError = false;
	while (properties.time < c::finalTime) {
		execute();
		if (crossCheck()) {
			hasError = true;
		}
	}
	crossCheck(true);
	std::cout << properties.showHead();
	std::cout << properties.show();
	if (hasError) {
		std::cout << "Error encountered through simulation" << std::endl;
	} else {
		std::cout << "OK" << std::endl;
	}
	utils::saveFile("test.pdb", lattice.gridToPdb());
	utils::loadInJMol("test.pdb");
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
		Molecule& molecule = lattice.moleculeVector()[*it];
		int64_t oldBounds = molecule.bounds();
		int64_t newBounds = lattice.recalculateBounds(*it);

		for (int64_t direction = 0; direction < c::nDiffusions; ++direction) {
			if (molecule.diffEvent(Diffusion(direction)) != c::empty) {
				eventLists.properDiffEventReplace(*it, Diffusion(direction), oldBounds);
			}
		}
		for (int64_t rotation = 0; rotation < c::nRotations; ++rotation) {
			if (molecule.rotEvent(Rotation(rotation)) != c::empty) {
				eventLists.properRotEventReplace(*it, Rotation(rotation), oldBounds);
			}
		}

		for (int64_t direction = 0; direction < c::nDiffusions; ++direction) {
			assert(molecule.diffEvent(Diffusion(direction)) == c::empty);
			if (lattice.isFree(*it, diffusionResolver[direction], molecule.rotation)) {
				eventLists.properDiffEventAddition(*it, Diffusion(direction), newBounds);
			}
		}
		for (int64_t rotation = 0; rotation < c::nRotations; ++rotation) {
			assert(molecule.rotEvent(Rotation(rotation)) == c::empty);
			if (lattice.isFree(*it, Position(0, 0), Rotation(rotation))) {
				eventLists.properRotEventAddition(*it, Rotation(rotation), newBounds);
			}
		}

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
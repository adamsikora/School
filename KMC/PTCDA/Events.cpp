
#include "FileUtils.h"

#include "Events.h"

void Events::simulation() {
	bool hasError = false;
	while (lattice.coverage() < c::finalCoverage) {
		execute();
		//if (crossCheck()) {
		//	hasError = true;
		//}
	}
	crossCheck(true);
	std::cout << properties.showHead();
	std::cout << properties.show();
	if (hasError) {
		std::cout << "Error encountered through simulation" << std::endl;
	} else {
		std::cout << "OK" << std::endl;
	}
	std::cout << "Diff barrier = " << E_d << std::endl;
	countBounds();
	std::cout << std::endl;

	std::stringstream name;
	name << "double" << E_d << ".pdb";
	utils::saveFile(name.str(), lattice.gridToPdb());
	//utils::loadInJMol(name.str());
}

void Events::execute() {
	rates._setSums(eventLists._diffEvents);

	properties.time -= log(_random.get01()) / rates._total;

startOver:

	double chooseEvent = (rates._total) * _random.get01();

	if (chooseEvent < rates._totalAds) {
		int pom = static_cast<int> ((chooseEvent / rates._totalAds) * c::A);
		Position pomPos(pom % c::w, pom / c::w);

		if (molDescent(pomPos)) {
			lattice.addMolecule(pomPos);
			alterEvents(pomPos);
			properties.nAds++, properties.nEvents++;
		} else {
			goto startOver;
		}
	} else {
		chooseEvent -= rates._totalAds;
		double cumulateRates = 0;
		int ei = 0, ej = 0;
		while (cumulateRates + rates._sumsofDiff[ei] < chooseEvent)
			cumulateRates += rates._sumsofDiff[ei++];
		ej = static_cast<int> (floor((chooseEvent - cumulateRates) / rates._diff[ei]));

		DiffusionEvent diffEvent = eventLists._diffEvents[ei][ej];
		lattice.moveMolecule(diffEvent);
		for (int64_t direction = 0; direction < c::nDiffusions; ++direction) {
			if (lattice[diffEvent.moleculePos].diffEvent(Diffusion(direction)) != c::empty) {
				eventLists.properDiffEventReplace(lattice[diffEvent.moleculePos], Diffusion(direction), lattice[diffEvent.moleculePos].bounds);
			}
		}
		alterEvents(diffEvent.moleculePos);
		properties.nDiff++, properties.nEvents++;
	}
}

void Events::alterEvents(Position pos) {
	std::vector<Position> toAlter = lattice.getSetToAlter(pos);

	for (auto it = toAlter.begin(); it != toAlter.end(); it++) {
		GridCell& molecule = lattice[*it];
		int64_t oldBounds = molecule.bounds;
		int64_t newBounds = lattice.recalculateBounds(*it);

		for (int64_t direction = 0; direction < c::nDiffusions; ++direction) {
			if (molecule.diffEvent(Diffusion(direction)) != c::empty) {
				eventLists.properDiffEventReplace(molecule, Diffusion(direction), oldBounds);
			}
		}

		for (int64_t direction = 0; direction < c::nDiffusions; ++direction) {
			assert(molecule.diffEvent(Diffusion(direction)) == c::empty);
			if (lattice[*it + c::ptcdaLength * diffusionResolver[direction]].atomType == AtomType::empty &&
					lattice[*it + c::ptcdaLength * diffusionResolver[direction] + diffusionResolver[direction]].atomType == AtomType::empty) {
				eventLists.properDiffEventAddition(*it, Diffusion(direction), newBounds);
			}
		}
	}
}

bool Events::molDescent(Position& pos) {
	for (int64_t tries = 0; tries < 100; ++tries) {
		if (lattice.isFree(pos)) {
			return true;
		} else {
			int64_t type = _random.getIntFrom0To(2 + 2 * c::ptcdaWidth);
			if (type < 2) {
				pos = pos + Position(0, (type == 0) ? 1 : -1);
			} else {
				type -= 2;
				pos = pos + Position((type < c::ptcdaWidth) ? 1 : -1, 0);
			}
			pos.normalize();
		}
	}
	return false;
}

void Events::countBounds() {
	std::vector<int64_t> boundsPerType(c::ptcdaBondLength, 0);
	double totalBounds = 0;
	for (int64_t i = 0; i < c::A; ++i) {
		if (lattice._grid[i].atomType != AtomType::empty) {
			int64_t temp = lattice._grid[i].bounds;
			for (int64_t j = 0; j < c::boundsPerType; ++j) {
				if (temp % c::boundTypes != 0) {
					++boundsPerType[temp % c::boundTypes - 1];
					++totalBounds;
					temp /= c::boundTypes;
				}
			}
		}
	}
	for (int64_t i = 0; i < c::ptcdaBondLength; ++i) {
		std::cout << c::ptcdaBondLength - i - 1 << " common dimers: " << boundsPerType[i] / double(totalBounds) << std::endl;
	}
}

int64_t Events::crossCheck(bool correctResultsReporting) {
	int64_t molCount = 0;
	for (int64_t i = 0; i < c::A; ++i) {
		if (lattice._grid[i].atomType != AtomType::empty) {
			++molCount;
		}
	}
	if (molCount != properties.nAds) {
		std::cout << "mol count should be " << properties.nAds << " but is " << molCount << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "count OK" << std::endl;
	}
	// collision checking
	int64_t nCrowded = 0;
	for (int64_t j = 0; j < c::h; ++j) {
		for (int64_t i = 0; i < c::w; ++i) {
			if (lattice._grid[lattice.to1D(i, j)].atomType != AtomType::empty) {
				for (int64_t k = 1; k < c::ptcdaLength; ++k) {
					if (lattice._grid[lattice.to1D(i + k, j)].atomType != AtomType::empty)
						++nCrowded;
					if (lattice._grid[lattice.to1D(i - k, j)].atomType != AtomType::empty)
						++nCrowded;
				}
			}
		}
	}
	if (nCrowded > 0) {
		std::cout << "crowded counts:" << nCrowded << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "crowd OK" << std::endl;
	}
	// bounds checking
	int64_t nBadBounds = 0;
	for (int64_t i = 0; i < c::w; ++i) {
		for (int64_t j = 0; j < c::h; ++j) {
			if (lattice[Position(i, j)].atomType != AtomType::empty) {
				int64_t old = lattice[Position(i, j)].bounds;
				if (lattice.recalculateBounds(Position(i, j)) != old) {
					++nBadBounds;
				}
			}
		}
	}
	if (nBadBounds > 0) {
		std::cout << "bad bounds count:" << nBadBounds << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "bounds OK" << std::endl;
	}
	// correct diff links forward
	int64_t nBadForwardLinks = 0;
	for (int64_t i = 0; i < c::A; ++i) {
		if (lattice._grid[i].atomType != AtomType::empty) {
			if (lattice._grid[i].diffEvent(Diffusion::d10) != c::empty) {
				DiffusionEvent diff = eventLists._diffEvents[lattice._grid[i].bounds][lattice._grid[i].diffEvent(Diffusion::d10)];
				if (diff.movement != Diffusion::d10 || lattice.to1D(diff.moleculePos) != i) {
					++nBadForwardLinks;
				}
			}
			if (lattice._grid[i].diffEvent(Diffusion::d_10) != c::empty) {
				DiffusionEvent diff = eventLists._diffEvents[lattice._grid[i].bounds][lattice._grid[i].diffEvent(Diffusion::d_10)];
				if (diff.movement != Diffusion::d_10 || lattice.to1D(diff.moleculePos) != i) {
					++nBadForwardLinks;
				}
			}
		}
	}
	if (nBadForwardLinks > 0) {
		std::cout << "bad forward links:" << nBadBounds << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "forward links OK" << std::endl;
	}

	// correct diff links backward
	int64_t nBadBackwardLinks = 0;
	for (int64_t i = 0; i < c::maxBoundCount; ++i) {
		for (uint64_t j = 0; j < eventLists._diffEvents[i].size(); ++j) {
			DiffusionEvent diff = eventLists._diffEvents[i][j];
			if (lattice[diff.moleculePos].atomType == AtomType::empty || lattice[diff.moleculePos].bounds != i || lattice[diff.moleculePos].diffEvent(diff.movement) != j) {
				++nBadBackwardLinks;
			}
		}
	}
	if (nBadBackwardLinks > 0) {
		std::cout << "bad backward links:" << nBadBounds << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "backward links OK" << std::endl;
	}

	return nCrowded;
}
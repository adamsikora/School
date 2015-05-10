
#include "Events.h"

int64_t Events::crossCheck(bool correctResultsReporting) {
	auto mol = lattice.moleculeVector();
	// check that each molecule owns its space in grid
	int64_t nCrowded = 0;
	for (size_t i = 0; i < mol.size(); ++i) {
		for (auto &ligand : mol[i].moleculeType->ligands) {
			GridCell &gCell = lattice._grid[lattice.to1D(mol[i].position + ligand.position.rotate(mol[i].rotation))];
			if (gCell.atomType != ligand.type || gCell.molecule != i) {
				++nCrowded;
			}
		}
		GridCell &gCell = lattice._grid[lattice.to1D(mol[i].position)];
		if (gCell.atomType != AtomType::bulk || gCell.molecule != i) {
			++nCrowded;
		}
	}
	if (nCrowded > 0) {
		//assert(!"crowded counts");
		std::cout << "crowded counts:" << nCrowded << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "crowd OK" << std::endl;
	}

	// check correctness of stored bound count
	int64_t nBadBoundCounts = 0;
	for (size_t i = 0; i < mol.size(); ++i) {
		if (mol[i].bounds() != lattice.recalculateBounds(i)) {
			++nBadBoundCounts;
		}
	}
	if (nBadBoundCounts > 0) {
		//assert(!"bad counts");
		std::cout << "bad counts:" << nBadBoundCounts << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "counts OK" << std::endl;
	}

	// check correctness of links between eventlists and moleculelist todo
	int64_t nBadDiffsForward = 0, nBadRotsForward = 0;
	for (size_t i = 0; i < c::maxBoundCount; ++i) {
		for (size_t j = 0; j < eventLists._diffEvents[i].size(); ++j) {
			if (mol[eventLists._diffEvents[i][j].molecule].bounds() != i
					|| mol[eventLists._diffEvents[i][j].molecule].diffEvent(eventLists._diffEvents[i][j].movement) != j) {
				++nBadDiffsForward;
			}
		}
		for (size_t j = 0; j < eventLists._rotEvents[i].size(); ++j) {
			if (mol[eventLists._rotEvents[i][j].molecule].bounds() != i
					|| mol[eventLists._rotEvents[i][j].molecule].rotEvent(eventLists._rotEvents[i][j].rotation) != j) {
				++nBadRotsForward;
			}
		}
	}
	if (nBadDiffsForward > 0) {
		//assert(!"bad diffs forward");
		std::cout << "bad diffs forward:" << nBadDiffsForward << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "diffs forward OK" << std::endl;
	}
	if (nBadRotsForward > 0) {
		//assert(!"bad rots forward");
		std::cout << "bad rots forward:" << nBadRotsForward << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "rots forward OK" << std::endl;
	}

	int64_t nBadDiffsBackward = 0, nBadRotsBackward = 0;
	for (size_t i = 0; i < mol.size(); ++i) {
		auto &molec = mol[i];
		for (size_t j = 0; j < c::nDiffusions; ++j) {
			if (molec.diffEvent(Diffusion(j)) != c::empty) {
				DiffusionEvent &diffEvent = eventLists._diffEvents[molec.bounds()][molec.diffEvent(Diffusion(j))];
				if (diffEvent.molecule != i || diffEvent.movement != Diffusion(j)) {
					++nBadDiffsBackward;
				}
			}
		}
		for (size_t j = 0; j < c::nRotations; ++j) {
			if (molec.rotEvent(Rotation(j)) != c::empty) {
				RotationEvent &rotEvent = eventLists._rotEvents[molec.bounds()][molec.rotEvent(Rotation(j))];
				if (rotEvent.molecule != i || rotEvent.rotation != Rotation(j)) {
					++nBadRotsBackward;
				}
			}
		}
	}
	if (nBadDiffsBackward > 0) {
		//assert(!"bad diffs backward");
		std::cout << "bad diffs backward:" << nBadDiffsBackward << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "diffs backward OK" << std::endl;
	}
	if (nBadRotsBackward > 0) {
		//assert(!"bad rots backward");
		std::cout << "bad rots backward:" << nBadRotsBackward << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "rots backward OK" << std::endl;
	}

	// check correctness of events in eventlist todo
	int64_t nBadDiffs = 0, nBadRots = 0;
	for (size_t i = 0; i < mol.size(); ++i) {
		auto &molec = mol[i];
		for (size_t j = 0; j < c::nDiffusions; ++j) {
			if (molec.diffEvent(Diffusion(j)) != c::empty && !lattice.isFree(i, diffusionResolver[j], molec.rotation)) {
				++nBadDiffs;
			}
		}
		for (size_t j = 0; j < c::nRotations; ++j) {
			if (molec.rotEvent(Rotation(j)) != c::empty && !lattice.isFree(i, Position(0, 0), Rotation(j))) {
				++nBadRots;
			}
		}
	}
	if (nBadDiffs > 0) {
		//assert(!"bad diffs backward");
		std::cout << "bad diffs:" << nBadDiffs << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "diffs OK" << std::endl;
	}
	if (nBadRots > 0) {
		//assert(!"bad rots backward");
		std::cout << "bad rots:" << nBadRots << std::endl;
	} else if (correctResultsReporting) {
		std::cout << "rots OK" << std::endl;
	}


	return nCrowded + nBadBoundCounts + nBadDiffsForward + nBadRotsForward
		+ nBadDiffsBackward + nBadRotsBackward + nBadDiffs + nBadRots;
}
#include "Events.h"

void Events::crossCheck()
{
	bool badDiffLenght = false, badRotLenght = false, badDiffCross = false, badRotCross = false;
	int badDiffEvents = 0, badRotEvents = 0;
	bool badMolAlign = false, badGridState = false, badBounds = false;

	std::vector<int> pocetDiff(c::maxBoundCount, 0);
	for (std::vector<Molecule>::iterator it = grid._molecules.begin(); it != grid._molecules.end(); it++)
	for (int i = 0; i < 4; i++)
	if (it->getDiffEventPoint(i) != c::empty)
		pocetDiff[it->getBounds()]++;

	for (int i = 0; i < c::maxBoundCount; i++)
	if (eventLists._diffEvents[i].size() != pocetDiff[i])
		badDiffLenght = true;

	for (int h = 0; h < c::maxBoundCount; h++)
	for (unsigned i = 0; i < eventLists._diffEvents[h].size(); i++)
	if (i != grid._molecules[eventLists._diffEvents[h][i].iMol].getDiffEventPoint(eventLists._diffEvents[h][i].shift))
		badDiffCross = true;

	std::vector<int> pocetRot(c::maxBoundCount, 0);
	for (std::vector<Molecule>::iterator it = grid._molecules.begin(); it != grid._molecules.end(); it++)
	for (int i = 0; i < 2; i++)
	if (it->getRotEventPoint(i) != c::empty)
		pocetRot[it->getBounds()]++;

	for (int i = 0; i < c::maxBoundCount; i++)
	if (eventLists._rotEvents[i].size() != pocetRot[i])
		badRotLenght = true;

	for (int h = 0; h < c::maxBoundCount; h++)
	for (unsigned i = 0; i < eventLists._rotEvents[h].size(); i++)
	if (i != grid._molecules[eventLists._rotEvents[h][i].iMol].getRotEventPoint(eventLists._rotEvents[h][i].rot))
		badRotCross = true;

	
	for (unsigned pos = 0; pos < grid._molecules.size(); pos++) {
		for (int i = 0; i < 4; i++) {
			if ((grid._molecules[pos].getDiffEventPoint(i) != c::empty) != grid.isMoveFree(pos, i))
				badDiffEvents++;
		}
		for (int i = 0; i < 2; i++) {
			if ((grid._molecules[pos].getRotEventPoint(i) != c::empty) != grid.isRotFree(pos, i))
				badRotEvents++;
		}
	}


	std::vector<int> checkGrid(c::A, c::empty);

	for (unsigned pos = 0; pos < grid._molecules.size(); pos++) {
		Borders bord(grid._molecules[pos]);
		for (int i = bord.starty; i < bord.endyp1; i++)
			for (int j = bord.startx; j < bord.endxp1; j++) {
				if (checkGrid[to1D(j, i)] != c::empty)
					badMolAlign = true;
				checkGrid[to1D(j, i)] = pos;
			}

		std::vector<Ligand>& pomlig = grid._molecules[pos].getligands();
		for (std::vector<Ligand>::iterator lig_it = pomlig.begin(); lig_it != pomlig.end(); lig_it++)
			checkGrid[to1D(grid._molecules[pos].getligpos(lig_it->coord))] += lig_it->type * c::maxMolecules;
	}

	for (int i = 0; i < c::A; i++)
		if (checkGrid[i] != grid._lattice[i].cell)
			badGridState = true;

	for (unsigned pos = 0; pos < grid._molecules.size(); pos++) {
		int b[3] = { 0, 0, 0 };
		int bounds = 0;
		std::vector<Ligand>& pomlig = grid._molecules[pos].getligands();
		for (std::vector<Ligand>::iterator lig_it = pomlig.begin(); lig_it != pomlig.end(); lig_it++)
			if (grid._lattice[to1D(grid._molecules[pos].getligpos(lig_it->reach))].cell / c::maxMolecules)
				b[lig_it->type + grid._lattice[to1D(grid._molecules[pos].getligpos(lig_it->reach))].cell / c::maxMolecules - 2]++;

			bounds = b[0] + b[1] * c::boundsSep + b[2] * c::boundsSep * c::boundsSep;
		if (bounds != grid._molecules[pos].getBounds())
			badBounds = true;
	}


	std::cout << "Integrity check:" << std::endl;

	std::cout << "delka diff seznamu     " << (badDiffLenght	 ? "BAD!" : "ok") << std::endl;
	std::cout << "delka rot  seznamu     " << (badRotLenght	 ? "BAD!" : "ok") << std::endl;
	std::cout << "sparovani diff seznamu " << (badDiffCross	 ? "BAD!" : "ok") << std::endl;
	std::cout << "sparovani rot  seznamu " << (badRotCross    ? "BAD!" : "ok") << std::endl;
	std::cout << "obsah diff seznamu     " << (badDiffEvents  ? "BAD!" : "ok") << badDiffEvents << std::endl;
	std::cout << "obsah rot  seznamu     " << (badRotEvents   ? "BAD!" : "ok") << badRotEvents << std::endl;
	std::cout << "molecule align         " << (badMolAlign	 ? "BAD!" : "ok") << std::endl;
	std::cout << "grid state             " << (badGridState   ? "BAD!" : "ok") << std::endl;
	std::cout << "bound counts           " << (badBounds      ? "BAD!" : "ok") << std::endl;

	std::cout << std::endl;
	bool celkem = badDiffLenght || badRotLenght || badDiffCross || badRotCross ||
					  badDiffEvents || badRotEvents || badMolAlign || badGridState || badBounds;
	std::cout << "celkove                " << (celkem ? "BAD!  ERROR!!  BAD!" : "ok") << std::endl;
}

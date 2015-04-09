#include "Grid.h"


void Grid::printMolecule(int pos)
{
	const Borders bord(_molecules[pos]);
	for (int i = bord.starty; i < bord.endyp1; i++)
		for (int j = bord.startx; j < bord.endxp1; j++)
			_lattice[to1D(j, i)].set(pos);

	std::vector<Ligand>& pomlig = _molecules[pos].getligands();
	for (std::vector<Ligand>::iterator lig_it = pomlig.begin(); lig_it != pomlig.end(); lig_it++)
		_lattice[to1D(_molecules[pos].getligpos(lig_it->coord))].set(pos, lig_it->type);
}

void Grid::deprintMolecule(int pos)
{
	const Borders bord(_molecules[pos]);
	for (int i = bord.starty; i < bord.endyp1; i++)
		for (int j = bord.startx; j < bord.endxp1; j++)
			_lattice[to1D(j, i)].unset();
}

int Grid::freeCount(const Molecule& mol)
{
	int temp = 0;
	const Borders bord(mol);
	for (int i = bord.starty; i < bord.endyp1; i++)
		for (int j = bord.startx; j < bord.endxp1; j++)
			if (_lattice[to1D(j, i)].cell == c::empty)
				temp++;
	return temp;
}

bool Grid::isMoveFree(int pos, int shift)
{
	const Borders bord(_molecules[pos], shift, 0);
	for (int i = bord.starty; i < bord.endyp1; i++)
		for (int j = bord.startx; j < bord.endxp1; j++) {
			int pom = _lattice[to1D(j, i)].cell;
			if (pom != c::empty && pom % c::maxMolecules != pos)
				return false;
		}
	return true;
}
bool Grid::isRotFree(int pos, int rot)
{
	const Borders bord(_molecules[pos], c::rotation[rot]);
	for (int i = bord.starty; i < bord.endyp1; i++)
		for (int j = bord.startx; j < bord.endxp1; j++) {
			int pom = _lattice[to1D(j, i)].cell;
			if (pom != c::empty && pom % c::maxMolecules != pos)
				return false;
		}
	return true;
}

bool Grid::molDescent(Molecule& mol)
{
	int molA = mol.getA();
	if (molA == freeCount(mol))
		return true;

	int nFreeSpace;
	int nNewFreespace[5];

	while (true) {
		nFreeSpace = freeCount(mol);
		for (int i = 0; i < 4; i++) {
			mol.translate(c::movement[i]);
			nNewFreespace[i] = freeCount(mol);
			mol.translate(c::movement[(i + 2) % 4]);
		}
		mol.rotate(c::clockWise);
		nNewFreespace[4] = freeCount(mol);
		mol.rotate(c::counterWise);

		int max = 0;
		int maxpos = -1;
		for (int i = 0; i < 5; i++)
		if (nNewFreespace[i] > max) {
			max = nNewFreespace[i];
			maxpos = i;
		}
		if (maxpos == 4)
			mol.rotate(c::clockWise);
		else
			mol.translate(c::movement[maxpos]);

		if (max <= nFreeSpace)
			return false;
		else if (max == molA)
			return true;
	}
}

void Grid::boundCount(Molecule& mol)
{
	int b[3] = { 0, 0, 0 };
	int nBounds = 0;
	std::vector<Ligand>& pomlig = mol.getligands();
	for (std::vector<Ligand>::iterator lig_it = pomlig.begin(); lig_it != pomlig.end(); lig_it++)
		if (_lattice[to1D(mol.getligpos(lig_it->reach))].cell / c::maxMolecules) {
			b[lig_it->type + _lattice[to1D(mol.getligpos(lig_it->reach))].cell / c::maxMolecules - 2]++;
		}
		nBounds = b[0] + b[1] * c::boundsSep + b[2] * c::boundsSep * c::boundsSep;
	mol.setBounds(nBounds);
}

std::set<int> Grid::getSetToAlter(int pos)
{
	std::set<int> toReturn;

	const Borders bord(2, _molecules[pos]);
	for (int i = bord.starty; i < bord.endyp1; i++)
	for (int j = bord.startx; j < bord.endxp1; j++) {
		int pom = _lattice[to1D(j, i)].cell % c::maxMolecules;
		if (pom != c::empty && pom != pos)
			toReturn.insert(pom);
	}
	toReturn.insert(pos);

	return toReturn;
}

int Grid::addMolecule(Molecule &mol)
{
	_molecules.push_back(mol);
	printMolecule(_molecules.size() - 1);
	return _molecules.size() - 1;
}

int Grid::moveMolecule(MoleculeDiffEvent &mde)
{
	deprintMolecule(mde.iMol);
	_molecules[mde.iMol].translate(c::movement[mde.shift]);
	printMolecule(mde.iMol);
	return mde.iMol;
}

int Grid::rotateMolecule(MoleculeRotEvent &mre)
{
	deprintMolecule(mre.iMol);
	_molecules[mre.iMol].rotate(c::rotation[mre.rot]);
	printMolecule(mre.iMol);
	return mre.iMol;
}

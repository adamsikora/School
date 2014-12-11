/*

*/

#ifndef GRID_H
#define GRID_H

#include "Includes.h"

#include "Molecule.h"


inline int to1D(int x, int y)
{
	return ((x < 0 || x >= c::w) ? (x + c::w) % c::w : x) +
		c::w * ((y < 0 || y >= c::h) ? (y + c::h) % c::h : y);
}

inline int to1D(Coord p)
{
	return ((p.x < 0 || p.x >= c::w) ? (p.x + c::w) % c::w : p.x) +
		c::w * ((p.y < 0 || p.y >= c::h) ? (p.y + c::h) % c::h : p.y);
}

class Events;

class GridCell
{
public:
	GridCell() : cell(c::empty) {}
	GridCell(int partof, int ligand) : cell(ligand * c::maxMolecules + partof) {}

	inline void set(int partof, int ligand) { cell = ligand * c::maxMolecules + partof; }
	inline void set(int partof) { cell = partof; }
	inline void unset() { cell = c::empty; }

	int cell;

};

class Grid
{
public:
	Grid() : _lattice(c::A, GridCell()) {}

	void printMolecule(int posinMolList);
	void deprintMolecule(int posinMolList);

	int freeCount(const Molecule& mol);
	bool isMoveFree(int posinMolList, int shift);
	bool isRotFree(int posinMolList, int rot);
	bool molDescent(Molecule& mol);

	void boundCount(Molecule& mol);

	std::set<int> Grid::getSetToAlter(int pos);

	int addMolecule(Molecule &mol);
	int moveMolecule(MoleculeDiffEvent &mde);
	int rotateMolecule(MoleculeRotEvent &mre);

	friend class Events;

private:
	std::vector<GridCell> _lattice;
	std::vector<Molecule> _molecules;

};

#endif //GRID_H
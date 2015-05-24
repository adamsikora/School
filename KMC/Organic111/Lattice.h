#pragma once


#include "Molecule.h"


inline std::string getAtomType(AtomType atomType) {
	switch (atomType) {
	case AtomType::bulk: return " Ag";
	case AtomType::oxygen: return " O ";
	case AtomType::nitrogen: return " U ";
	default: assert(!"Shold never get here"); return "";
	}
}

struct GridCell {
	GridCell() : molecule(c::empty), atomType(AtomType::empty) {};
	void setCell(int64_t molec, AtomType atomtype) { molecule = molec; atomType = atomtype; }
	void setEmpty() { molecule = c::empty; atomType = AtomType::empty; }

	bool differentMolecule(int64_t moleculePos) const {
		return molecule != moleculePos && molecule != c::empty;
	}

	int64_t molecule;
	AtomType atomType;
};

class Events;

class Lattice {
public:
	Lattice() : _grid(c::A, GridCell()) {};

	int64_t addMolecule(Molecule molecule);
	int64_t moveMolecule(DiffusionEvent de);
	int64_t rotateMolecule(RotationEvent re);

	std::vector<Molecule>& moleculeVector() { return _molecules; }

	bool isFree(int64_t molecule, Position shift, Rotation rotation) const;
	int64_t occupiedCount(const Molecule& mol) const;
	bool molDescent(Molecule& mol) const;
	std::set<int64_t> getSetToAlter(int64_t pos) const;
	int64_t recalculateBounds(int64_t pos);

	std::string gridToPdb() const;

	friend class Events;

private:
	inline int64_t to1D(int64_t x, int64_t y) const {
		return ((x < 0 || x >= c::w) ? (x + c::w) % c::w : x) +
			c::w * ((y < 0 || y >= c::h) ? (y + c::h) % c::h : y);
	}
	inline int64_t to1D(Position pos) const {
		return ((pos.x() < 0 || pos.x() >= c::w) ? (pos.x() + c::w) % c::w : pos.x()) +
			c::w * ((pos.y() < 0 || pos.y() >= c::h) ? (pos.y() + c::h) % c::h : pos.y());
	}

	void printMolecule(const Molecule& molecule, int64_t position);
	void dePrintMolecule(const Molecule& molecule);

	std::vector<GridCell> _grid;
	std::vector<Molecule> _molecules;
};
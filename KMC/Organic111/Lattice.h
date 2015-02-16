#pragma once


#include "Molecule.h"


inline std::string getAtomType(AtomType atomType) {
	switch (atomType) {
	case AtomType::bulk: return " Ag";
	case AtomType::oxygen: return " O ";
	case AtomType::nitrogen: return " N ";
	default: assert(!"Shold never get here"); break;
	}
}

struct GridCell {
	GridCell() : molecule(-1), atomType(AtomType::empty) {};

	uint64_t molecule;
	AtomType atomType;
};

class Lattice {
public:
	Lattice() : _grid(c::A, GridCell()) {};

	void addMolecule(Molecule molecule) {
		_molecules.push_back(molecule);
		printMolecule(molecule);
	}

	void printMolecule(Molecule molecule);
	std::string gridToPdb() const;

private:
	inline uint64_t to1D(uint64_t x, uint64_t y) const {
		return ((x < 0 || x >= c::w) ? (x + c::w) % c::w : x) +
			c::w * ((y < 0 || y >= c::h) ? (y + c::h) % c::h : y);
	}
	std::vector<GridCell> _grid;
	std::vector<Molecule> _molecules;
};
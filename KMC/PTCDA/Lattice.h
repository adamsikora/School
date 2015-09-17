#pragma once

#include "BaseClass.h"

inline std::string getAtomType(AtomType atomType) {
	switch (atomType) {
		case AtomType::bulk: return " Ag";
		case AtomType::oxygen: return " O ";
		case AtomType::nitrogen: return " U ";
		default: assert(!"Should never get here"); return "";
	}
}

class Lattice {
public:
	Lattice() : _grid(c::A, GridCell()) {};
	Lattice& operator=(const Lattice&) = delete;
	Lattice(const Lattice&) = delete;

	void addMolecule(Position pos);
	void moveMolecule(DiffusionEvent de);

	bool isFree(Position pos) const;
	std::vector<Position> getSetToAlter(Position pos) const;
	int64_t recalculateBounds(Position pos);

	double coverage();

	std::string gridToPdb() const;

	GridCell& operator[](Position pos) {
		return _grid[to1D(pos)];
	}

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

	std::vector<GridCell> _grid;
};
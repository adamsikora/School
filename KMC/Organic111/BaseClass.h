#pragma once

#include "StlBase.h"
#include "Constants.h"

class Position {
public:
	Position() : _x(0), _y(0) {};
	Position(int64_t x, int64_t y) : _x(x), _y(y) {};

	int64_t x() const { return _x; }
	int64_t y() const { return _y; }
	void move(Position pos) { _x += pos.x(); _y += pos.y(); }
	int64_t area() const { return _x * _y; }

private:
	int64_t _x, _y;
};

enum class Rotation {
	zero = 0, pithird = 1, twopithird = 2,
};

enum class AtomType {
	empty, bulk, oxygen, nitrogen,
};

class Ligand {
public:
	Ligand(AtomType ligandType, Position position)
		: type(ligandType), position(position) {};

	AtomType type;
	Position position;
};
#pragma once

#include "StlBase.h"
#include "Constants.h"

enum class Rotation {
	zero = 0, pithird = 1, twopithird = 2,
};

class Position {
public:
	Position() : _x(0), _y(0) {};
	Position(int64_t x, int64_t y) : _x(x), _y(y) {};

	int64_t x() const { return _x; }
	int64_t y() const { return _y; }
	void move(Position pos) { _x += pos.x(); _y += pos.y(); }
	int64_t area() const { return _x * _y; }

	const Position rotate(Rotation rot) const {
		if (rot == Rotation::zero) return Position(this->_x, this->_y);
		if (rot == Rotation::pithird) return Position(this->_y, - this->_x - this->_y);
		if (rot == Rotation::twopithird) return Position(- this->_y - this->_x, this->_x);
	}

private:
	int64_t _x, _y;
};

Position operator+(const Position& lhs, const Position& rhs);
Position operator-(const Position& lhs, const Position& rhs);

enum class Diffusion {
	d10 = 0, d01 = 1, d_11 = 2, d_10 = 3, d0_1 = 4, d1_1 = 5,
};

const Position diffusionResolver[6]{
	Position(1, 0),
	Position(0, 1),
	Position(-1, 1),
	Position(-1, 0),
	Position(0, -1),
	Position(1, -1),
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
#pragma once

#include "Constants.h"

class Position {
public:
	Position() : _x(0), _y(0) {};
	Position(int64_t x, int64_t y) : _x(x), _y(y) {};

	int64_t x() const { return _x; }
	int64_t y() const { return _y; }
	void move(Position pos) { _x += pos.x(); _y += pos.y(); }
	int64_t area() const { return _x * _y; }
	void normalize() {
		if (_x < 0 || _x >= c::w) {
			_x = (_x + c::w) % c::w;
		}
		if (_y < 0 || _y >= c::h) {
			_y = (_y + c::h) % c::h;
		}
	}

private:
	int64_t _x, _y;
};

Position operator+(const Position& lhs, const Position& rhs);
Position operator-(const Position& lhs, const Position& rhs);
Position operator*(int64_t lhs, const Position& rhs);
bool operator<(const Position& lhs, const Position& rhs);

enum class Diffusion {
	d10 = 0, d_10 = 1,
};

const Position diffusionResolver[2] {
	Position(1, 0),
	Position(-1, 0),
};

enum class AtomType {
	empty, bulk, oxygen, nitrogen,
};

struct DiffusionEvent {
	DiffusionEvent(Position moleculePos, Diffusion movement)
		: moleculePos(moleculePos), movement(movement) {
	};
	Position moleculePos;
	Diffusion movement;
};

struct GridCell {
	GridCell() : atomType(AtomType::empty), bounds(0) {
		posInEventList[0] = posInEventList[1] = c::empty;
	};
	//GridCell& operator=(const GridCell&) = delete;
	//GridCell(const GridCell&) = delete;

	void setCell(AtomType atomtype) {
		atomType = atomtype;
	}
	void setEmpty() {
		atomType = AtomType::empty;
	}
	void setDiffEvent(Diffusion shift, int64_t newPos) {
		posInEventList[static_cast<int64_t>(shift)] = newPos;
	}
	int64_t diffEvent(Diffusion shift) const {
		return posInEventList[static_cast<int64_t>(shift)];
	}

	AtomType atomType;
	int64_t posInEventList[2];
	int64_t bounds;
};
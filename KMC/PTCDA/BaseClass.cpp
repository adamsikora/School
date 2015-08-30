#include "BaseClass.h"

Position operator+(const Position& lhs, const Position& rhs) {
	return Position(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

Position operator-(const Position& lhs, const Position& rhs) {
	return Position(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

Rotation operator+(const Rotation& lhs, const Rotation& rhs) {
	return Rotation(static_cast<Rotation>((static_cast<int64_t>(lhs) + static_cast<int64_t>(rhs)) % c::nRotations));
}

Rotation operator-(const Rotation& lhs, const Rotation& rhs) {
	return Rotation(static_cast<Rotation>((static_cast<int64_t>(lhs) - static_cast<int64_t>(rhs) + c::nRotations) % c::nRotations));
}
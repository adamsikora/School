#include "BaseClass.h"

Position operator+(const Position& lhs, const Position& rhs) {
	return Position(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

Position operator-(const Position& lhs, const Position& rhs) {
	return Position(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}
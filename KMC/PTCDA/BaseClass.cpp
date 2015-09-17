#include "BaseClass.h"

Position operator+(const Position& lhs, const Position& rhs) {
	return Position(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

Position operator-(const Position& lhs, const Position& rhs) {
	return Position(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

Position operator*(int64_t lhs, const Position& rhs) {
	return Position(lhs*rhs.x(), lhs*rhs.y());
}

bool operator<(const Position& lhs, const Position& rhs) {
	if (lhs.x() < rhs.y()) {
		return true;
	} else {
		return lhs.y() < rhs.y();
	}
}
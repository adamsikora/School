#include "Lattice.h"

bool Lattice::isFree(Position pos) const {
	for (int64_t i = - c::ptcdaLength + 1 - 1; i < c::ptcdaLength + 1; ++i) {
		if (_grid[to1D(pos.x() + i, pos.y())].atomType != AtomType::empty) {
			return false;
		}
	}
	return true;
}

std::vector<Position> Lattice::getSetToAlter(Position pos) const {
	std::vector<Position> result;
	for (int64_t y = pos.y() - 1; y <= pos.y() + 1; ++y) {
		for (int64_t x = pos.x() - c::ptcdaBondLength - 1; x <= pos.x() + c::ptcdaBondLength + 1; ++x) {
			if (_grid[to1D(x, y)].atomType != AtomType::empty) {
				result.push_back(Position(x, y));
			}
		}
	}
	return std::move(result);
}

int64_t Lattice::recalculateBounds(Position pos) {
	int64_t result = 0;
	assert(_grid[to1D(pos)].atomType != AtomType::empty);
	for (int64_t i = 0; i < c::ptcdaBondLength; ++i) {
		if (_grid[to1D(pos.x() + i, pos.y() + 1)].atomType != AtomType::empty)
			result += (i + 1);
		if (_grid[to1D(pos.x() + i, pos.y() - 1)].atomType != AtomType::empty)
			result += (i + 1) * c::boundTypes;
	}
	for (int64_t i = 1; i < c::ptcdaBondLength; ++i) {
		if (_grid[to1D(pos.x() - i, pos.y() + 1)].atomType != AtomType::empty)
			result += (i + 1) * c::boundTypes * c::boundTypes;
		if (_grid[to1D(pos.x() - i, pos.y() - 1)].atomType != AtomType::empty)
			result += (i + 1) * c::boundTypes * c::boundTypes * c::boundTypes;
	}
	assert(result < c::maxBoundCount);
	_grid[to1D(pos)].bounds = result;

	return result;
}

double Lattice::coverage() {
	int64_t count = 0;
	for (int64_t i = 0; i < c::A; ++i) {
		if (_grid[i].atomType != AtomType::empty) {
			++count;
		}
	}
	return double(count*c::ptcdaLength) / c::A;
}

void Lattice::addMolecule(Position pos) {
	assert(isFree(pos));
	_grid[to1D(pos)].atomType = AtomType::bulk;
}

void Lattice::moveMolecule(DiffusionEvent de) {
	assert(_grid[to1D(de.moleculePos)].atomType == AtomType::bulk);
	_grid[to1D(de.moleculePos)].atomType = AtomType::empty;
	_grid[to1D(de.moleculePos + diffusionResolver[static_cast<int>(de.movement)])].atomType = AtomType::bulk;
}

std::string Lattice::gridToPdb() const {
	bool rect = true;
	std::stringstream ss;

	ss << "REMARK jmolscript: color cpk" << std::endl;

	ss << std::fixed;

	double dist = 3.0;
	int line = 1;
	double x, y, z, t;
	for (int pi = 0; pi < c::w; pi++) {
		for (int pj = 0; pj < c::h; pj++) {
			for (int64_t i = 1; i < 3; ++i) {
				x = dist*pi;
				y = -dist*(4*pj + i);
				z = -dist;
				t = 0.1 * 0;

				ss << "ATOM  "
					<< std::setw(5) << line++ << " Tl   UNK     0    "
					<< std::setw(8) << std::setprecision(3) << x
					<< std::setw(8) << std::setprecision(3) << y
					<< std::setw(8) << std::setprecision(3) << z
					<< std::setw(6) << std::setprecision(2) << 0.0
					<< std::setw(6) << std::setprecision(2) << t
					<< "  0" << "\n";
			}
		}
	}
	for (int pi = 0; pi < c::w; pi++) {
		for (int pj = 0; pj < c::h; pj++) {
			if (_grid[to1D(pi, pj)].atomType != AtomType::empty) {
				for (int64_t i = 0; i < c::ptcdaLength; ++i) {
					for (int64_t j = 0; j < 4; ++j) {
						x = dist*((pi + i)%c::w);
						y = -dist*(4*pj + j);
						z = 0;
						t = 0.1 * 0;

						ss << "ATOM  "
							<< std::setw(5) << line++
							<< " Mn   UNK     0    "
							<< std::setw(8) << std::setprecision(3) << x
							<< std::setw(8) << std::setprecision(3) << y
							<< std::setw(8) << std::setprecision(3) << z
							<< std::setw(6) << std::setprecision(2) << 0.0
							<< std::setw(6) << std::setprecision(2) << t
							<< "  0" << "\n";
					}
				}
			}
		}
	}
	return ss.str();
}
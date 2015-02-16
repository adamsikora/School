#include "Lattice.h"

void Lattice::printMolecule(Molecule molecule) {
	if (molecule.rotation == Rotation::zero) {
		for (int64_t x = molecule.startX(); x < molecule.endX(); ++x) {
			for (int64_t y = molecule.startY(); y < molecule.endY(); ++y) {
				_grid[to1D(molecule.position.x() + x - ((y + 6) / 2 - 3), molecule.position.y() + y)].atomType = AtomType::bulk;
			}
		}
		for (auto && ligand : molecule.moleculeType->ligands) {
			_grid[to1D(molecule.position.x() + ligand.position.x() - ((ligand.position.y() + 6) / 2 - 3), molecule.position.y() + ligand.position.y())].atomType = ligand.type;
		}
	} else if (molecule.rotation == Rotation::pithird) {
		for (int64_t x = molecule.startX(); x < molecule.endX(); ++x) {
			for (int64_t y = molecule.startY(); y < molecule.endY(); ++y) {
				_grid[to1D(molecule.position.x() + y, molecule.position.y() - x + ((y + 6) / 2 - 3) - y)].atomType = AtomType::bulk;
			}
		}
		for (auto && ligand : molecule.moleculeType->ligands) {
			_grid[to1D(molecule.position.x() + ligand.position.y(), molecule.position.y() - ligand.position.x() + ((ligand.position.y() + 6) / 2 - 3) - ligand.position.y())].atomType = ligand.type;
		}
	} else if (molecule.rotation == Rotation::twopithird) {
		for (int64_t x = molecule.startX(); x < molecule.endX(); ++x) {
			for (int64_t y = molecule.startY(); y < molecule.endY(); ++y) {
				_grid[to1D(molecule.position.x() - y - x + ((y + 6) / 2 - 3), molecule.position.y() + x - ((y + 6) / 2 - 3))].atomType = AtomType::bulk;
			}
		}
		for (auto && ligand : molecule.moleculeType->ligands) {
			_grid[to1D(molecule.position.x() - ligand.position.y() - ligand.position.x() + ((ligand.position.y() + 6) / 2 - 3), molecule.position.y() + ligand.position.x() - ((ligand.position.y() + 6) / 2 - 3))].atomType = ligand.type;
		}
	} else {
		assert(!"invalid rotation");
	}
	_grid[to1D(molecule.position.x(), molecule.position.y())].atomType = AtomType::oxygen;
}

std::string Lattice::gridToPdb() const {
	bool rect = true;
	std::stringstream ss;

	ss << "REMARK jmolscript: color cpk" << std::endl;

	ss << std::fixed;

	double dist = 3.450;
	int line = 1;
	double x, y, z, t;
	for (int pi = 0; pi < c::h; pi++) {
		for (int pj = 0; pj < c::w; pj++) {
			x = dist*(pj + 0.5*(pi - 1));
			y = -sqrt(3.0) / 2.0*dist*(pi + 1.0 / 3.0*(-1));
			z = sqrt(2.0 / 3.0)*dist*(-1);
			t = 0.1 * 0;

			if (rect) {
				if ((pi) / 2 + pj > c::w - 1) {
					x -= c::w * dist;
				}
			}
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
	for (int pi = 0; pi < c::w; pi++) {
		for (int pj = 0; pj < c::h; pj++) {
			if (_grid[to1D(pi, pj)].atomType != AtomType::empty) {
				x = dist*(pi + 0.5*(pj - 1));
				y = -sqrt(3.0) / 2.0*dist*(pj + 1.0 / 3.0*(-1));
				z = sqrt(2.0 / 3.0)*dist*(0);
				t = 0.1 * 0;

				if (rect) {
					if ((pj) / 2 + pi > c::w - 1) {
						x -= c::w * dist;
					}
				}
				ss << "ATOM  "
					<< std::setw(5) << line++
					<< getAtomType(_grid[to1D(pi, pj)].atomType)
					<< "   UNK     0    "
					<< std::setw(8) << std::setprecision(3) << x
					<< std::setw(8) << std::setprecision(3) << y
					<< std::setw(8) << std::setprecision(3) << z
					<< std::setw(6) << std::setprecision(2) << 0.0
					<< std::setw(6) << std::setprecision(2) << t
					<< "  0" << "\n";
			}
		}
	}
	return ss.str();
}
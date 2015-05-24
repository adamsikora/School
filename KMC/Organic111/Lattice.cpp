#include "Lattice.h"

void Lattice::printMolecule(const Molecule& molecule, int64_t index) {
	for (auto &ligand : molecule.moleculeType->ligands) {
		_grid[to1D(molecule.position + ligand.position.rotate(molecule.rotation))].setCell(index, ligand.type);
	}
	_grid[to1D(molecule.position.x(), molecule.position.y())].setCell(index, AtomType::bulk);
}

void Lattice::dePrintMolecule(const Molecule& molecule) {
	for (auto &ligand : molecule.moleculeType->ligands) {
		_grid[to1D(molecule.position + ligand.position.rotate(molecule.rotation))].setEmpty();
	}
	_grid[to1D(molecule.position.x(), molecule.position.y())].setEmpty();
}

bool Lattice::isFree(int64_t moleculePos, Position shift, Rotation rotation) const {
	const Molecule& molecule = _molecules[moleculePos];
	for (auto &ligand : molecule.moleculeType->ligands) {
		if (_grid[to1D(molecule.position + shift + ligand.position.rotate(rotation))].differentMolecule(moleculePos)) {
			return false;
		}
	}
	if (_grid[to1D(molecule.position + shift)].differentMolecule(moleculePos)) {
		return false;
	}
	return true;
}

int64_t Lattice::occupiedCount(const Molecule& molecule) const {
	int64_t result = 0;
	for (auto &ligand : molecule.moleculeType->ligands) {
		if (_grid[to1D(molecule.position + ligand.position.rotate(molecule.rotation))].differentMolecule(c::empty)) {
			++result;
		}
	}
	if (_grid[to1D(molecule.position)].differentMolecule(c::empty)) {
		++result;
	}
	return result;
}

bool Lattice::molDescent(Molecule& mol) const { // fucked up
	if (occupiedCount(mol) == 0)
		return true;

	int64_t nOccupiedSpace;
	int64_t nNewOccupiedSpace[c::nDiffusions + c::nRotations];

	while (true) {
		nOccupiedSpace = occupiedCount(mol);
		Position oldPosition(mol.position);
		for (int64_t i = 0; i < c::nDiffusions; i++) {
			mol.position.move(diffusionResolver[i]);
			nNewOccupiedSpace[i] = occupiedCount(mol);
			mol.position = oldPosition;
		}

		Rotation oldRotation(mol.rotation);
		for (int64_t i = 0; i < c::nRotations; i++) {
			mol.rotation = static_cast<Rotation>(i);
			nNewOccupiedSpace[i + c::nDiffusions] = occupiedCount(mol);
			mol.rotation = oldRotation;
		}

		int64_t min = nOccupiedSpace;
		int64_t minpos = -1;
		for (int i = 0; i < c::nDiffusions + c::nRotations; i++) // cunarnicka ale spravne
			if (nNewOccupiedSpace[i] < min) {
				min = nNewOccupiedSpace[i];
				minpos = i;
			}
		if (minpos < c::nDiffusions)
			mol.position.move(diffusionResolver[minpos]);
		else
			mol.rotation = static_cast<Rotation>(minpos - c::nDiffusions); // cunarnicka ale spravne

		if (min == nOccupiedSpace)
			return false;
		else if (min == 0)
			return true;
	}
}

std::set<int64_t> Lattice::getSetToAlter(int64_t moleculePos) const {
	std::set<int64_t> result;
	const Molecule& molecule = _molecules[moleculePos];
	const int64_t margin = 5;
	for (int64_t x = -margin; x <= margin; ++x) {
		for (int64_t y = -margin; y <= margin; ++y) {
			int64_t moleculeNumber = _grid[to1D(molecule.position.x() + x, molecule.position.y() + y)].molecule;
			if (moleculeNumber != moleculePos && moleculeNumber != c::empty) {
				result.insert(moleculeNumber);
			}
		}
	}
	result.insert(moleculePos);

	return std::move(result);
}

int64_t Lattice::recalculateBounds(int64_t moleculePos) {
	Molecule& molecule = _molecules[moleculePos];
	int64_t N_N = 0, N_O = 0, O_O = 0;
	for (auto &ligand : molecule.moleculeType->ligands) {
		for (const Position &displacement : diffusionResolver) {
			size_t index = to1D(molecule.position + ligand.position.rotate(molecule.rotation) + displacement);
			if (_grid[index].differentMolecule(moleculePos)) {
				if (ligand.type == AtomType::nitrogen) {
					if (_grid[index].atomType == AtomType::nitrogen) { ++N_N; }
					if (_grid[index].atomType == AtomType::oxygen) { ++N_O; }
				} else if (ligand.type == AtomType::oxygen) {
					if (_grid[index].atomType == AtomType::nitrogen) { ++N_O; }
					if (_grid[index].atomType == AtomType::oxygen) { ++O_O; }
				}
			}
		}
	}
	int64_t result = c::getBoundCount(N_N, N_O, O_O);
	molecule.setBounds(result);
	return result;
}

int64_t Lattice::addMolecule(Molecule molecule) {
	_molecules.push_back(molecule);
	printMolecule(molecule, _molecules.size() - 1);
	return _molecules.size() - 1;
}

int64_t Lattice::moveMolecule(DiffusionEvent de) {
	dePrintMolecule(_molecules[de.molecule]);
	_molecules[de.molecule].position.move(diffusionResolver[static_cast<int64_t>(de.movement)]);
	printMolecule(_molecules[de.molecule], de.molecule);
	return de.molecule;
}

int64_t Lattice::rotateMolecule(RotationEvent re) {
	dePrintMolecule(_molecules[re.molecule]);
	_molecules[re.molecule].rotation = re.rotation;
	printMolecule(_molecules[re.molecule], re.molecule);
	return re.molecule;
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
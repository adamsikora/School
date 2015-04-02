#include "FileUtils.h"
#include "JMol.h"

#include "Lattice.h"


int main() {
	Lattice lattice;
	std::vector<Molecule> molecules{
		Molecule(Position(1, 2), Rotation::zero, phthalocyanine),
		Molecule(Position(6, 7), Rotation::pithird, phthalocyanine),
		Molecule(Position(11, 12), Rotation::twopithird, phthalocyanine),

		Molecule(Position(20, 10), Rotation::zero, phthalocyanine),
		Molecule(Position(23, 11), Rotation::zero, phthalocyanine),
		Molecule(Position(26, 7), Rotation::zero, phthalocyanine),
		//Molecule(Position(25, 13), Rotation::zero, phthalocyanine),

		Molecule(Position(-10, 30), Rotation::zero, phthalocyanine),
		Molecule(Position(-5, 24), Rotation::zero, phthalocyanine),
		Molecule(Position(-1, 26), Rotation::zero, phthalocyanine),
		Molecule(Position(-6, 32), Rotation::zero, phthalocyanine)
	};
	for (auto &&molecule : molecules) {
		lattice.addMolecule(molecule);
	}

	utils::saveFile("test.pdb", lattice.gridToPdb());
	utils::loadInJMol("test.pdb");

	return 0;
};
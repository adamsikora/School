#include "FileUtils.h"
#include "JMol.h"

#include "Lattice.h"


int main() {
	Lattice lattice;
	std::vector<Molecule> molecules{
		Molecule(Position(2, 3), Rotation::zero, phthalocyanine),
		Molecule(Position(12, 13), Rotation::pithird, phthalocyanine),
		Molecule(Position(22, 23), Rotation::twopithird, phthalocyanine),

		Molecule(Position(30, 30), Rotation::zero, phthalocyanine),
		Molecule(Position(29, 36), Rotation::zero, phthalocyanine),
		Molecule(Position(36, 27), Rotation::zero, phthalocyanine),
		Molecule(Position(35, 33), Rotation::zero, phthalocyanine),

		Molecule(Position(0, 30), Rotation::zero, phthalocyanine),
		Molecule(Position(5, 24), Rotation::zero, phthalocyanine),
		Molecule(Position(9, 26), Rotation::zero, phthalocyanine),
		Molecule(Position(4, 32), Rotation::zero, phthalocyanine)
	};
	for (auto &&molecule : molecules) {
		lattice.addMolecule(molecule);
	}
	utils::saveFile("test.pdb", lattice.gridToPdb());
	utils::loadInJMol("test.pdb");
	return 0;
};
#pragma once

#include "BaseClass.h"


class MoleculeType {
public:
	MoleculeType(Position size, Position center, std::vector<Ligand> ligands)
		: size(size), center(center), ligands(ligands) {};

//private:
	const Position size, center;
	const std::vector<Ligand> ligands;
};

typedef std::shared_ptr<MoleculeType> MoleculeTypePtr;

const MoleculeTypePtr phthalocyanine =
	std::make_shared<MoleculeType>(
			Position(5, 6),
			Position(2, 2),
			std::vector<Ligand>{
	Ligand(AtomType::oxygen, Position(-2, -2)),
		Ligand(AtomType::oxygen, Position(2, -2)),
		Ligand(AtomType::oxygen, Position(-2, 3)),
		Ligand(AtomType::oxygen, Position(2, 3)),
		Ligand(AtomType::nitrogen, Position(0, -2)),
		Ligand(AtomType::nitrogen, Position(0, 3)),
		Ligand(AtomType::nitrogen, Position(-2, 1)),
		Ligand(AtomType::nitrogen, Position(2, 0)),
		/*Ligand(AtomType::nitrogen, Position(-2, -2)),
		Ligand(AtomType::nitrogen, Position(-2, -1)),
		Ligand(AtomType::nitrogen, Position(-2, 0)),
		Ligand(AtomType::nitrogen, Position(-2, 1)),
		Ligand(AtomType::nitrogen, Position(-2, 2)),
		Ligand(AtomType::nitrogen, Position(-2, 3)),
		Ligand(AtomType::oxygen, Position(-1, 3)),
		Ligand(AtomType::oxygen, Position(0, 3)),
		Ligand(AtomType::oxygen, Position(1, 3)),
		Ligand(AtomType::oxygen, Position(2, 3))*/
			}
	);

class Molecule {
public:
	Molecule(Position position, Rotation rotation, /*const */MoleculeTypePtr moleculeType)
		: position(position), rotation(rotation), moleculeType(moleculeType) {};

	inline int64_t startX() { return - moleculeType->center.x(); }
	inline int64_t endX()   { return - moleculeType->center.x() + moleculeType->size.x(); }
	inline int64_t startY() { return - moleculeType->center.y(); }
	inline int64_t endY()   { return - moleculeType->center.y() + moleculeType->size.y(); }

	/*const */MoleculeTypePtr moleculeType;
	Position position;
	Rotation rotation;

};
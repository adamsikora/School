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

const MoleculeTypePtr phthalocyanineOld =
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
const MoleculeTypePtr phthalocyanineNOld =
std::make_shared<MoleculeType>(
Position(0, 0),
Position(0, 0),
std::vector<Ligand>{
	Ligand(AtomType::oxygen, Position(0, -2)),
		Ligand(AtomType::oxygen, Position(0, 2)),
		Ligand(AtomType::oxygen, Position(2, -1)),
		Ligand(AtomType::oxygen, Position(-2, 1)),
		Ligand(AtomType::nitrogen, Position(0, -1)),
		Ligand(AtomType::nitrogen, Position(1, -1)),
		Ligand(AtomType::nitrogen, Position(1, 0)),
		Ligand(AtomType::nitrogen, Position(0, 1)),
		Ligand(AtomType::nitrogen, Position(-1, 1)),
		Ligand(AtomType::nitrogen, Position(-1, 0)),
}

);
const MoleculeTypePtr phthalocyanine =
std::make_shared<MoleculeType>(
Position(0, 0),
Position(0, 0),
std::vector<Ligand>{
	Ligand(AtomType::oxygen, Position(0, -2)),
		Ligand(AtomType::oxygen, Position(0, 2)),
		Ligand(AtomType::oxygen, Position(2, -1)),
		Ligand(AtomType::oxygen, Position(-2, 1)),
		Ligand(AtomType::oxygen, Position(-1, -1)),
		Ligand(AtomType::oxygen, Position(1, 1)),
		Ligand(AtomType::oxygen, Position(2, -2)),
		Ligand(AtomType::oxygen, Position(-2, 2)),
		Ligand(AtomType::nitrogen, Position(0, -1)),
		Ligand(AtomType::nitrogen, Position(1, -1)),
		Ligand(AtomType::nitrogen, Position(1, 0)),
		Ligand(AtomType::nitrogen, Position(0, 1)),
		Ligand(AtomType::nitrogen, Position(-1, 1)),
		Ligand(AtomType::nitrogen, Position(-1, 0)),
}
);

class Molecule {
public:
	Molecule(Position position, Rotation rotation, /*const */MoleculeTypePtr moleculeType)
		: position(position), rotation(rotation), moleculeType(moleculeType), _bounds(0),
		_transEvents(c::defaultDiffusions), _rotEvents(c::defaultRotations) {};

	//inline int64_t startX() const { return - moleculeType->center.x(); }
	//inline int64_t endX()   const { return - moleculeType->center.x() + moleculeType->size.x(); }
	//inline int64_t startY() const { return - moleculeType->center.y(); }
	//inline int64_t endY()   const { return - moleculeType->center.y() + moleculeType->size.y(); }

	void setDiffEvent(Diffusion direction, int64_t posinEventList) { _transEvents[static_cast<int64_t>(direction)] = posinEventList; }
	void setRotEvent(Rotation direction, int64_t posinEventList) { _rotEvents[static_cast<int64_t>(direction)] = posinEventList; }
	int64_t diffEvent(Diffusion direction) const { return _transEvents[static_cast<int64_t>(direction)]; }
	int64_t rotEvent(Rotation direction) const { return _rotEvents[static_cast<int64_t>(direction)]; }
	void setBounds(int64_t bounds) { _bounds = bounds; }
	int64_t bounds() const { return _bounds; }

	/*const */MoleculeTypePtr moleculeType;
	Position position;
	Rotation rotation;

private:
	int64_t _bounds;
	std::array<int64_t, c::nDiffusions> _transEvents;
	std::array<int64_t, c::nRotations> _rotEvents;
};

struct DiffusionEvent {
	DiffusionEvent(int64_t molecule, Diffusion movement)
		: molecule(molecule), movement(movement) {};
	int64_t molecule;
	Diffusion movement;
};

struct RotationEvent {
	RotationEvent(int64_t molecule, Rotation rotation)
		: molecule(molecule), rotation(rotation) {};
	int64_t molecule;
	Rotation rotation;
};
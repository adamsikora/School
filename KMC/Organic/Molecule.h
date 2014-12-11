/*

*/

#ifndef MOLEC_H
#define MOLEC_H

#include <vector>
#include <set>
#include <math.h>

#include "Consts.h"
#include "Class.h"


class MoleculeType
{
public:
	MoleculeType() : _size(0, 0) {}
	MoleculeType(int type)
   {
      _size = Coord(2, 2);
      _ligands = {
         Ligand(Coord(2, 0), Coord(3, 0), c::ligandTypes[0]),
         Ligand(Coord(0, 2), Coord(0, 3), c::ligandTypes[0]),
         Ligand(Coord(-2, 0), Coord(-3, 0), c::ligandTypes[0]),
         Ligand(Coord(0, -2), Coord(0, -3), c::ligandTypes[0]),
         Ligand(Coord(2, 2), Coord(2, 3), c::ligandTypes[1]),
         Ligand(Coord(-2, 2), Coord(-3, 2), c::ligandTypes[1]),
         Ligand(Coord(-2, -2), Coord(-2, -3), c::ligandTypes[1]),
         Ligand(Coord(2, -2), Coord(3, -2), c::ligandTypes[1])
      };
      /*_size = Coord(2, 2);
      _ligands = {
         Ligand(Coord(2, 1), Coord(3, -1), c::ligandTypes[0]),
         Ligand(Coord(-1, 2), Coord(1, 3), c::ligandTypes[0]),
         Ligand(Coord(-2, -1), Coord(-3, 1), c::ligandTypes[0]),
         Ligand(Coord(1, -2), Coord(-1, -3), c::ligandTypes[0])
      };*/
		/*_size = Coord(4, 1);
		_ligands = {
			Ligand(Coord(4, 0), Coord(5, 0), c::ligandTypes[0]),
			Ligand(Coord(0, 1), Coord(0, 2), c::ligandTypes[1]),
			Ligand(Coord(-4, 0), Coord(-5, 0), c::ligandTypes[0]),
			Ligand(Coord(0, -1), Coord(0, -2), c::ligandTypes[1])
		};*/
      /*_size = Coord(3, 2);
      _ligands = {
         Ligand(Coord(2, 2), Coord(2, 3), c::ligandTypes[0]),
         Ligand(Coord(-2, -2), Coord(-2, -3), c::ligandTypes[0])
      };*/
	}

	int getsizex() const { return _size.x; }
	int getsizey() const { return _size.y; }

protected:
	Coord _size;
	std::vector<Ligand> _ligands;

};


class MoleculeDiffEvent
{
public:
	MoleculeDiffEvent(int transDir, int posinVector) : shift(transDir), iMol(posinVector) {}

	int iMol;
	int shift;

};

class MoleculeRotEvent
{
public:
	MoleculeRotEvent(int rotDir, int posinVector) : rot(rotDir), iMol(posinVector) {}

	int iMol;
	int rot;

};

class Molecule : public MoleculeType
{
public:
	Molecule(int molType, const Coord &pos, int rot)
		: MoleculeType(molType), _pos(pos), _rot(rot), nBounds(0) {
		for (int i = 0; i < 4; i++) _transEvents[i] = -1;
		for (int i = 0; i < 2; i++) _rotEvents[i] = -1;
	}

	int getposx() const { return _pos.x; }
	int getposy() const { return _pos.y; }
	int getA() const { return (2 * _size.x + 1) * (2 * _size.y + 1); }

	int getstartx() const { return _pos.x - ((_rot % 2) ? _size.y : _size.x); }
	int getendx()   const { return _pos.x + ((_rot % 2) ? _size.y : _size.x); }
	int getstarty() const { return _pos.y - ((_rot % 2) ? _size.x : _size.y); }
	int getendy()   const { return _pos.y + ((_rot % 2) ? _size.x : _size.y); }

	int getstartx(int rotate) const { return _pos.x - (((_rot + 1) % 2) ? _size.y : _size.x); }
	int getendx  (int rotate) const { return _pos.x + (((_rot + 1) % 2) ? _size.y : _size.x); }
	int getstarty(int rotate) const { return _pos.y - (((_rot + 1) % 2) ? _size.x : _size.y); }
	int getendy  (int rotate) const { return _pos.y + (((_rot + 1) % 2) ? _size.x : _size.y); }

	Coord getligpos(Coord iLig) const { return _pos + iLig.rotate(_rot); }

	void translate(const Coord &transDir)
	{
		_pos.x = (_pos.x + transDir.x + c::w) % c::w, _pos.y = (_pos.y + transDir.y + c::h) % c::h;
	}
	void rotate(int rotDir) { _rot += rotDir; }

	std::vector<Ligand>& getligands() { return _ligands; }

	void setDiffEventPoint(int transDir, int posinEventList) { _transEvents[transDir] = posinEventList; }
	void setRotEventPoint(int rotDir, int posinEventList) { _rotEvents[rotDir] = posinEventList; }
	int getDiffEventPoint(int transDir) const { return _transEvents[transDir]; }
	int getRotEventPoint(int rotDir) const { return _rotEvents[rotDir]; }

	int getBounds() const { return nBounds; }
	void setBounds(int nB) { nBounds = nB; }

private:
	Coord _pos;
	unsigned _rot;

	int _transEvents[4];
	int _rotEvents[2];

	int nBounds;
};

class Borders
{
public :
	Borders(const Molecule& mol) :
		startx(mol.getstartx()), endxp1(mol.getendx() + 1),
		starty(mol.getstarty()), endyp1(mol.getendy() + 1) {}

	Borders(const Molecule& mol, int shift, int prebytecny)
	{
		switch (shift)
		{
		case 0:
			startx = mol.getendx() + 1;
			endxp1 = mol.getendx() + 2;
			starty = mol.getstarty();
			endyp1 = mol.getendy() + 1;
			break;
		case 1:
			startx = mol.getstartx();
			endxp1 = mol.getendx() + 1;
			starty = mol.getendy() + 1;
			endyp1 = mol.getendy() + 2;
			break;
		case 2:
			startx = mol.getstartx() - 1;
			endxp1 = mol.getstartx();
			starty = mol.getstarty();
			endyp1 = mol.getendy() + 1;
			break;
		case 3:
			startx = mol.getstartx();
			endxp1 = mol.getendx() + 1;
			starty = mol.getstarty() - 1;
			endyp1 = mol.getstarty();
			break;
		default:
			break;
		}
	}

	Borders(const Molecule& mol, int rot) :
		startx(mol.getstartx(1)), endxp1(mol.getendx(1) + 1),
		starty(mol.getstarty(1)), endyp1(mol.getendy(1) + 1) {}

	Borders(int extend, const Molecule& mol) :
		startx(mol.getstartx() - extend), endxp1(mol.getendx() + 1 + extend),
		starty(mol.getstarty() - extend), endyp1(mol.getendy() + 1 + extend) {}

	int startx, endxp1, starty, endyp1;
};


#endif //MOLEC_H
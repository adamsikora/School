#ifndef CLASS_H
#define CLASS_H


class Coord
{
public:
	Coord() : x(0), y(0) {}
	Coord(int a) : x(a), y(a) {}
	Coord(int a, int b) : x(a), y(b) {}
	inline int getA() const { return x * y; }
	inline Coord rotate(unsigned rot) const
	{
		switch (rot % 4)
		{
		case 0: return *this; break;
		case 1: return Coord( y, -x); break;
		case 2: return Coord(-x, -y); break;
		case 3: return Coord(-y,  x); break;
		default: std::cout << "bad rot"; return Coord();  break;
		}
	}
	inline Coord operator+(const Coord& b) const { return Coord(this->x + b.x, this->y + b.y); }

	int x, y;

};

class Ligand
{
public:
	Ligand() : coord(), reach(), type(0) {}
	Ligand(Coord c, Coord r, int type) : coord(c), reach(r), type(type) {}

	Coord coord;
	Coord reach;
	int type;

};

#endif // CLASS_H
/*
Adam Sikora
11.9.2013

*/

#include "Events.h"
#include "StopWatch.h"
#include "FileUtils.h"

class posit {
public:
	posit(int x, int y, double r, double d) : x(x), y(y), rotation(r), dimension(d) {};
	int x, y;
	double rotation;
	double dimension;
};

int main()
{
  utils::StopWatch sw;
	sw.start();

	std::ofstream file("test.pdb");

	file << "REMARK jmolscript: color cpk" << std::endl;

	file << std::fixed;

	double dist = 3.450;
	int line = 1;
	double x, y, z, t;
	for (int pi = 0; pi < c::h; pi++) {
		for (int pj = 0; pj < c::w; pj++) {
			x = dist*(pj + 0.5*(pi - 1));
			y = -sqrt(3.0) / 2.0*dist*(pi + 1.0 / 3.0*(-1));
			z = sqrt(2.0 / 3.0)*dist*(-1);
			t = 0.1 * 0;

			if (true) {
				if ((pi + 1) / 2 + pj > c::w - 1) {
					x -= c::w * dist - 0.5 * dist;
					y -= sqrt(3.0) / 2.0 * dist;
				}
			}
			file << "ATOM  "
				<< std::setw(5) << line++ << " Tl   UNK     0    "
				<< std::setw(8) << std::setprecision(3) << x
				<< std::setw(8) << std::setprecision(3) << y
				<< std::setw(8) << std::setprecision(3) << z
				<< std::setw(6) << std::setprecision(2) << 0.0
				<< std::setw(6) << std::setprecision(2) << t
				<< "  0" << "\n";
		}
	}
	std::vector<posit> mols;
	mols.emplace_back(0, c::w / 2, 0.0, 2);
	mols.emplace_back(7, c::w / 2 - 1, 1.0 / 3.0*3.1415, 2);
	mols.emplace_back(3, c::w / 2 - 6, 0.0, 2);
	mols.emplace_back(0, c::w / 2 + 10, 1.0 / 3.0*3.1415, 2);
	mols.emplace_back(-5, c::w / 2 + 15, 1.0 / 3.0*3.1415, 2);

	for (auto &&mol : mols) {
		for (int i = -mol.dimension; i <= mol.dimension; ++i) {
			for (int j = -mol.dimension; j <= mol.dimension; ++j) {
				x = dist*(mol.x + 0.5*mol.y + i*cos(mol.rotation) - j*sin(mol.rotation));
				y = -sqrt(3.0) / 2.0*dist*mol.y + dist*(j*cos(mol.rotation) + i*sin(mol.rotation));
				z = 0.0;
				t = 0.0;

				file << "ATOM  "
					<< std::setw(5) << line++ << ((abs(i) == mol.dimension || abs(j) == mol.dimension) ? " Si" : " Mn") << "   UNK     0    "
					<< std::setw(8) << std::setprecision(3) << x
					<< std::setw(8) << std::setprecision(3) << y
					<< std::setw(8) << std::setprecision(3) << z
					<< std::setw(6) << std::setprecision(2) << 0.0
					<< std::setw(6) << std::setprecision(2) << t
					<< "  0" << "\n";
			}
		}
	}
	file.close();
	utils::loadInJMol("test.pdb");

	//Events events;
	//events.simulation(50.0, 20);
	/*int poc = 25000000;
	while (poc--) {
		events.execute();
	}
	Output::pdbput(events.getMolec(), "01");*/
	/*events.noDep();
	poc = 10000000;
	while (poc--) {
		events.execute();
	}
	Output::pdbput(events.getMolec(), "02");*/
	//sw.stop();
	//events.report();
	//events.crossCheck();
	//std::cout << std::endl << "simulation time: " << sw.getLastElapsed() << std::endl;
	//
	//std::cin.ignore();
	return EXIT_SUCCESS;
}

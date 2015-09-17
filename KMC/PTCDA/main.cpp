#include "FileUtils.h"

#include "Lattice.h"
#include "Events.h"
#include "Constants.h"

int main() {
	std::string outFile = "separated.txt";
	remove(outFile.c_str());
	freopen(outFile.c_str(), "w", stdout);
	for (double ed = 1.7; ed >= 1.1; ed -= 0.05) {
		Events events(ed);
		events.simulation();
	}
	//Lattice lattice;
	//Position pos(5, 0);
	//lattice.addMolecule(pos);
	//for (int64_t i = -c::ptcdaLength; i <= c::ptcdaLength; ++i) {
	//	std::cout << lattice.isFree(pos + Position(i, 0));
	//}
	//utils::saveFile("test.pdb", lattice.gridToPdb());
	//utils::loadInJMol("test.pdb");
	std::cin.ignore();
	return 0;
};
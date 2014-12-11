#ifndef OUTPUT_H
#define OUTPUT_H

#include "Includes.h"
#include "Grid.h"

namespace Output
{
	void show(const std::vector<GridCell>& lattice);
	void pdbput(std::vector<Molecule>& molecules, std::string charakteristic = "");
   void report(std::string report, std::string characteristic = "");
	void data(std::vector<std::vector<double> >& data, std::string charakteristic = "");
}

#endif // OUTPUT_H
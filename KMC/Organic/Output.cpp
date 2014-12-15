#include "Output.h"

std::string pdbExtension = ".pdb";
std::string txtExtension = ".txt";

std::string pdbName = "pdbOutput";
std::string dataName = "dataOutput";
std::string reportName = "report";

std::string pdbAtoms[c::nLigandTypes + 1] = { " Ag", " O ", " N " };

void Output::show(const std::vector<GridCell>& lattice)
{
	for (int i = 0; i < (c::h < 21 ? c::h : 20); i++) {
		for (int j = 0; j < (c::w < 21 ? c::w : 20); j++) {
			if (lattice[to1D(j, i)].cell == c::empty)
				std::cout << c::printEmpty;
			else if (lattice[to1D(j, i)].cell < c::maxMolecules)
				std::cout << c::printBody;
			else if (lattice[to1D(j, i)].cell / c::maxMolecules == 1)
				std::cout << c::printLigandPlus;
			else if (lattice[to1D(j, i)].cell / c::maxMolecules == 2)
				std::cout << c::printLigandMinus;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Output::pdbput(std::vector<Molecule>& molecules, std::string charakteristic)
{
	std::string name = pdbName + charakteristic + pdbExtension;
	std::ofstream fout;

	fout.open(name, std::ios::out);

	if (!fout.is_open()) {
		std::cout << "malo pameti";
	}
	double dist = 2.50;
	int line = 1;
	fout << "REMARK jmolscript: color cpk" << std::endl;
	for (std::vector<Molecule>::iterator it = molecules.begin(); it != molecules.end(); it++) {
		Borders bord(-1, *it);
		for (int i = bord.starty; i < bord.endyp1; i++)
		for (int j = bord.startx; j < bord.endxp1; j++) {
			fout << "ATOM  " << std::setiosflags(std::ios_base::right) << std::setw(5) << line++
				<< pdbAtoms[0] << "   UNK     0    "
				<< std::setw(8) << std::setprecision(3) << std::fixed << dist * j	// x
				<< std::setw(8) << std::setprecision(3) << std::fixed << dist * i	// y
				<< std::setw(8) << std::setprecision(3) << std::fixed << 0.0		// z
				<< std::setw(6) << std::setprecision(2) << std::fixed << 0.0
				<< std::setw(6) << std::setprecision(2) << std::fixed << 0.0		// t
				<< "  0" << "\n";
		}
		std::vector<Ligand>& pomlig = it->getligands();
		for (std::vector<Ligand>::iterator lig_it = pomlig.begin(); lig_it != pomlig.end(); lig_it++) {
			fout << "ATOM  " << std::setiosflags(std::ios_base::right) << std::setw(5) << line++
				<< pdbAtoms[lig_it->type] << "   UNK     0    "
				<< std::setw(8) << std::setprecision(3) << std::fixed << dist * it->getligpos(lig_it->coord).x	// x
				<< std::setw(8) << std::setprecision(3) << std::fixed << dist * it->getligpos(lig_it->coord).y	// y
				<< std::setw(8) << std::setprecision(3) << std::fixed << 0.0		// z
				<< std::setw(6) << std::setprecision(2) << std::fixed << 0.0
				<< std::setw(6) << std::setprecision(2) << std::fixed << 0.0		// t
				<< "  0" << "\n";
		}
	}

	fout.close();
}

void Output::data(std::vector<std::vector<double> >& data, std::string charakteristic)
{
   std::string name = dataName + charakteristic + txtExtension;
   std::ofstream fout;

   fout.open(name, std::ios::out);

   if (!fout.is_open()) {
      std::cout << "malo pameti";
   }
   for (std::vector<std::vector<double> >::iterator it = data.begin(); it != data.end(); it++) {
      for (std::vector<double>::iterator jt = it->begin(); jt != it->end(); jt++)
         fout << *jt << "\t";
      fout << std::endl;
   }

   fout.close();
}


void Output::report(std::string report, std::string characteristic)
{
   std::string name = reportName + characteristic + txtExtension;
   std::ofstream fout;

   fout.open(name, std::ios::out);

   if (!fout.is_open()) {
      std::cout << "malo pameti";
   }
   
   fout << report;

   fout.close();
}
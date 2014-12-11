#include "Events.h"


void Events::simulation(double depositionTime, double multiple)
{
   _depoTime = depositionTime;
   while (getCoverage() < 0.15) {
      execute();
      if (_nEvents % 1000000 == 0) {
         std::cout << _nEvents / 1000000 << " " << _nAds << " " << _nDiff << std::endl;
         //std::stringstream ss;
         //ss << _nEvents / 1000000;
         //Output::pdbput(grid._molecules, ss.str());
      }
   }
   std::cout << _nEvents << std::endl;
   Output::pdbput(grid._molecules, "AfterDeposition");
   /*if (multiple > 0.0) {
      noDep();
      int depoEvents = static_cast<int> (_nEvents * multiple);
      std::cout << _nEvents << std::endl;
      for (int i = 0; i < depoEvents; i++) {
         execute();
         if (_nEvents % 1000000 == 0) {
            std::cout << _nEvents / 1000000 << " " << _nAds << " " << _nDiff << std::endl;
         }
      }
      Output::pdbput(grid._molecules, "AfterRelaxation");
   }*/
}

void Events::execute()
{
   rates._setSums(eventLists._diffEvents, eventLists._rotEvents);

   _time -= log(_trandom()) / rates._total;

startOver:

   double chooseEvent = (rates._totalAds + rates._totalDiff/* + rates._totalRot*/) * _random();

	if (chooseEvent < rates._totalAds) {
		int pom = static_cast<int> ((chooseEvent / rates._totalAds) *c::A * 4);
		Coord pomPos(pom % c::h, pom / 4 / c::h);
		int pomRot = pom / c::A;
		Molecule pomMol(1, pomPos, pomRot);

		if (grid.molDescent(pomMol))
			alterEvents(grid.addMolecule(pomMol)),
			_nAds++, _nEvents++;
		else
			goto startOver;
	}/*
	else if (chooseEvent < rates._totalAds + rates._totalRot) {
		chooseEvent -= rates._totalAds;
		double cumulateRates = 0;
		int ei = 0, ej = 0;
		while (cumulateRates + rates._sumsofRot[ei] < chooseEvent)
			cumulateRates += rates._sumsofRot[ei++];
		ej = static_cast<int> (floor((chooseEvent - cumulateRates) / rates._rot[ei]));

		alterEvents(grid.rotateMolecule(eventLists._rotEvents[ei][ej]));
      _nRot++, _nEvents++;
	}*/
	else {
		chooseEvent -= rates._totalAds/* + rates._totalRot*/;
		double cumulateRates = 0;
		int ei = 0, ej = 0;
		while (cumulateRates + rates._sumsofDiff[ei] < chooseEvent)
			cumulateRates += rates._sumsofDiff[ei++];
		ej = static_cast<int> (floor((chooseEvent - cumulateRates) / rates._diff[ei]));

		alterEvents(grid.moveMolecule(eventLists._diffEvents[ei][ej]));
      _nDiff++, _nEvents++;
	}
}

void Events::alterEvents(int posinMolList)
{
	std::set<int> toAlter = grid.getSetToAlter(posinMolList);

	for (std::set<int>::iterator it = toAlter.begin(); it != toAlter.end(); it++) {

		int oldBounds = grid._molecules[*it].getBounds();
		grid.boundCount(grid._molecules[*it]);
		int newBounds = grid._molecules[*it].getBounds();

		if (newBounds != oldBounds) {
			for (int i = 0; i < 4; i++)
				if (grid._molecules[*it].getDiffEventPoint(i) != c::empty)
						eventLists.properDiffEventReplace(*it, i, oldBounds);
			for (int i = 0; i < 2; i++)
				if (grid._molecules[*it].getRotEventPoint(i) != c::empty)
						eventLists.properRotEventReplace(*it, i, oldBounds);
		}

		for (int i = 0; i < 4; i++)
			if (grid._molecules[*it].getDiffEventPoint(i) == c::empty)
				if (grid.isMoveFree(*it, i))
					eventLists.properDiffEventAddition(*it, i, newBounds);
				else;
			else
				if (!grid.isMoveFree(*it, i))
					eventLists.properDiffEventReplace(*it, i, oldBounds);

		for (int i = 0; i < 2; i++)
			if (grid._molecules[*it].getRotEventPoint(i) == c::empty)
				if (grid.isRotFree(*it, i))
					eventLists.properRotEventAddition(*it, i, newBounds);
				else;
			else
				if (!grid.isRotFree(*it, i))
					eventLists.properRotEventReplace(*it, i, oldBounds);
	}
}

void Events::report()
{
   //Output::show(grid._lattice);
   //Output::pdbput(grid._molecules);

   std::stringstream ss;

   ss.setf(std::ios::scientific);
   ss << "deposition time:  " << std::setprecision(3) << _depoTime << std::endl;
   ss << "total time:       " << std::setprecision(3) << _time << std::endl;
   ss << "#molecules:  " << grid._molecules.size() << std::endl;
   ss << "coverage:    " << std::setprecision(5) << getCoverage() << std::endl;
   ss << "#events:     " << std::setprecision(3) << static_cast<double>(getnEvents()) << std::endl;
   ss << "#diffusions: " << std::setprecision(3) << static_cast<double>(getnDiff()) << std::endl;
   ss << "#rotations:  " << std::setprecision(3) << static_cast<double>(getnRot()) << std::endl;
   ss << std::endl;
   ss << std::endl;
   ss << "Molecule layout:" << std::endl;
   ss << std::endl;
   ss.unsetf(std::ios::floatfield);

   Molecule typic(1, Coord(0,0), 0);
   std::vector<std::vector<int>> molec(2 * typic.getsizey() + 1, std::vector<int>(2 * typic.getsizex() + 1, 0));

   std::vector<Ligand> lig = typic.getligands();
   for (std::vector<Ligand>::iterator it = lig.begin(); it != lig.end(); it++) {
      molec[typic.getsizey() + it->coord.y][typic.getsizex() + it->coord.x] = it->type;
   }

   for (std::vector<std::vector<int>>::iterator it = molec.begin(); it != molec.end(); it++) {
      for (std::vector<int>::iterator jt = it->begin(); jt != it->end(); jt++) {
         ss << *jt;
      }
      ss << std::endl;
   }

   ss << std::endl;
   ss << 0 << " - body" << std::endl;
   ss << c::ligandTypes[0] << " - first ligand" << std::endl;
   ss << c::ligandTypes[1] << " - second ligand" << std::endl;
   ss << std::endl;
   ss << std::endl;
   ss << "Atractive forces between ligands:" << std::endl;
   ss << std::endl;
   ss << "\t1\t2" << std::endl;
   ss << "1\t" << c::ligInter11 << "\t" << c::ligInter12 << std::endl;
   ss << "1\t" << c::ligInter12 << "\t" << c::ligInter22 << std::endl;
   ss << std::endl;
   ss << "lattice dim:      " << c::w << " x " << c::h << std::endl;
   ss << "ads rate:         " << c::adsRate << std::endl;
   ss << "diff rot barrier: " << c::E_b << std::endl;
   ss << "temperature:      " << c::T << std::endl;

   std::cout << ss.str();
   Output::report(ss.str());
}


Events events;
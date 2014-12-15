/*

*/

#ifndef CONSTS_H
#define CONSTS_H

#include "Class.h"

namespace c
{
	const int maxMolecules = 256 * 256 * 256;

	const int w = 256;
	const int h = w;
	const int A = w * h;

	const int empty = -1;

	const int nLigandTypes = 2;

	const int ligandTypes[nLigandTypes] = { 1, 2 };
	//const double ligandInteractions[nLigandTypes][nLigandTypes] = { { 1.0, -1.0 }, { -1.0, 1.0 } };
	const double ligInter11 = 0.0, ligInter12 = 0.25, ligInter22 = 0.0;

	const int boundsSep = 5;
	const int maxBoundCount = boundsSep * boundsSep * boundsSep;

	const Coord toRight(1, 0);
	const Coord toBottom(0, 1);
	const Coord toLeft(-1, 0);
	const Coord toTop(0, -1);

	const Coord movement[4] = { toRight, toBottom, toLeft, toTop };

	const int clockWise = 1;
	const int counterWise = -1;

	const int rotation[2] = { clockWise, counterWise };


	const std::string printEmpty("  ");
	const std::string printBody(2, char(176));
	const std::string printLigandPlus(2, char(178));
	const std::string printLigandMinus(2, char(219));

	const int seed = 13;

	const double adsRate = 0.000001;

	const double E_b = 0.5;
	const double boltzmann = 8.6173324e-5;
	const double nu = 1e13;
	const double T = 300.0;
}

#endif // CONSTS_H
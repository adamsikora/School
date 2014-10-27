/*
author: Adam Sikora

defines main class for KMC simulation

*/

#ifndef EVENTS_H
#define EVENTS_H

#include "Includes.h"

#include "Grid.h"
#include "Evolution.h"
#include "Eventlist.h"
#include "Neighborhood.h"
#include "Parameters.h"
#include "State.h"
#include "Reporter.h"

enum simulationReturn
{
   negligibleDiffusion, allright, excessiveDiffusion
};

class Events
{
public:
	//Events(Report& report);
	Events(State state);

   //simulationReturn desorptionSimulation();  // runs desorption simulation
   simulationReturn growthSimulation();      // runs growth simulation

	void execute();      // chooses simulation event
	void executeDes();   // chooses desorption event
   void evolve();       // time and temperature evolution throughout the simulation

	void adsorption(int position, atomType adatom);      // executes adsorption event
	void desorption(S desEvent); // executes desorption event
	void diffusion(SD diffEvent);// executes diffusion event

	void adsorbIslands(int nIslands, int islandSize);

   void deleteObsoleteEvents(int src, int dest);  // deletes outdated events
   void deleteObsoleteSrcEvents(int position);    // deletes outdated events with source atom on position
   void deleteObsoleteDestEvents(int position);   // deletes outdated events where position is event destination
   void addNewEvents(int src, int dest);          // adds new events
   void addNewSrcEvents(int src);                 // adds new events actual to source atom
   void addNewDestEvents(int dest);               // adds new events actual to destination position

	int crossCheck(bool showResults = true);    // checks state of class for possible errors for debugging only
	bool checkDiff(int supposedConf, SD conf);

private:
	ParametersInternal para;
	Parameters param;

	Reporter m_reporter;

   Evolution evolution;
	Grid grid;
	EventLists eventLists;

   const Rates& rates;

	unsigned __int64 _nEvents;
   unsigned __int64 _nAds, _nDiff, _nDes;// _nUpDiff, _nDownDiff, _nDes;// , _nFreeDes, _nFreeDiff;    // events counters
   inline unsigned __int64 _getnActions() const { return _nAds + _nDiff + _nDes; }
   unsigned __int64 _nMetal, _nSilicon;
	double _targetCoverage;

   std::vector<int> _nDesorbNeigh;

	inline double _getCoverage() {
      return static_cast<double> (_nMetal + _nSilicon) / c::A;
   }
   //int getnFreeAtoms();
   //int getnBorderAtoms();
   //double getEdes();

	//int _adsHeight;

	int _seed;
	MTRand _random;

   Results getResults();    // functions for passing simulation output
   //std::vector<double> getOtherData();

};

#endif //EVENTS_H
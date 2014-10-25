#pragma once

#include <set>
#include <bitset>
#include <memory>
#include <functional>
#include <random>
#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "Encoding.h"
#include "RandomUtils.h"

template <typename specimenType>
class Specimen {
public:
	Specimen<specimenType>(double mutationRate, specimenType value)
		: m_mutationRate(mutationRate), m_value(value)
	{
		m_fitness = m_fitnessFunction();
	}
	virtual std::string value() const
	{
		return std::string(); 
	}
	double fitness() const { return m_fitness; }
	Specimen mutate() const { return Specimen(*this); }
	Specimen reproduce(Specimen mate) const { return Specimen(*this); }

	friend bool operator < (Specimen<specimenType> lhs, Specimen<specimenType> rhs)
	{
		return lhs.fitness() < rhs.fitness();
	}
protected:
	double m_mutationRate;
	specimenType m_value;
	double m_fitness;

	virtual double m_fitnessFunction() { return 0; }
};

template <typename specimenType>
class BlindEvolution {
public:
	BlindEvolution(specimenType foreFather, uint64_t nIterations, double fitnessTarget, uint64_t nMutations, uint64_t nSurvivors, double mutationProb, double reproductionProb)
		: m_nIterations(nIterations), m_nMutations(nMutations), m_nSurvivors(nSurvivors),
		m_mutationProbability(mutationProb), m_reproductionProbability(reproductionProb), m_fitnessTarget(fitnessTarget)
	{
		m_specimens.insert(foreFather);
	}

	virtual void mutatePopulation()
	{
		std::multiset<specimenType> newGeneration;
		for (auto &specimen : m_specimens) {
			for (uint64_t i = 0; i < m_nMutations; ++i) {
				if (mersenneTwister() < m_mutationProbability*std::numeric_limits<uint64_t>::max()) {
					specimenType newsp = specimen.mutate();
					newGeneration.insert(newsp);
				}
			}
		}
		m_specimens.insert(newGeneration.begin(), newGeneration.end());
	}

	virtual void reproducePopulation()
	{
		//std::multiset<specimenType> newGeneration;
		//for (std::multiset<specimenType>::iterator it = m_specimens.begin(); it != m_specimens.end(); ++it) {
		//	std::multiset<specimenType>::iterator jt = it;
		//	++jt;
		//	for (jt; jt != m_specimens.end(); ++jt) {
		//		if (mersenneTwister() < m_reproductionProbability*std::numeric_limits<uint64_t>::max()) {
		//			specimenType newsp = it->reproduce(*jt);
		//			newGeneration.insert(newsp);
		//		}
		//	}
		//}
	};
	virtual void reducePopulation()
	{
		std::multiset<specimenType>::iterator it = m_specimens.begin();
		for (uint64_t i = 0; i < m_nSurvivors; ++i) {
			++it;
		}
		m_specimens.erase(it, m_specimens.end());
	}

	virtual void evolve() {
		for (uint64_t i = 0; i < m_nIterations; ++i) {
			double bestFitness = (m_specimens.begin())->fitness();
			mutatePopulation();
			reducePopulation();
			reproducePopulation();
			reducePopulation();
			if (bestFitness >(m_specimens.begin())->fitness()) {
				bestFitness = (m_specimens.begin())->fitness();
				std::cout << "new best result at: " << (m_specimens.begin())->value() << " with fitness value of: " << bestFitness << std::endl;
			}
			if (bestFitness < m_fitnessTarget) {
				break;
			}
		}
		std::cout << m_specimens.begin()->value() << std::endl;
	}

protected:
	std::multiset<specimenType> m_specimens;
	double m_mutationProbability, m_reproductionProbability, m_fitnessTarget;
	uint64_t m_nIterations, m_nMutations,  m_nSurvivors;
};


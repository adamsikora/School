#pragma once

#include "StlBase.h"
#include "RandomUtils.h"


class LearningEvolution {
public:
	LearningEvolution(
		uint64_t start, double learningRate, uint64_t nIterations, uint64_t nextGenSize, uint64_t nSurvivors,
		std::pair<double, double> bounds, std::function<double(double)> function
		)
		: m_bitProbability(64, 0.5), m_learningRate(learningRate), m_nIterations(nIterations), m_nextGenSize(nextGenSize),
		m_nSurvivors(nSurvivors), m_bounds(bounds), m_function(function)
	{
		m_specimens.insert(std::pair<double, uint64_t>(m_fitnessFunction(start), start));
	}

	void generateNextGen()
	{
		std::multimap<double, uint64_t> newGeneration;
		for (uint64_t i = 0; i < m_nextGenSize; ++i) {
			std::bitset<64> next;
			for (uint64_t j = 0; j < 64; ++j) {
				if (utils::decide(m_bitProbability[j])) {
					next[j] = 1;
				}
				else {
					next[j] = 0;
				}
			}
			uint64_t intNext = next.to_ullong();
			m_specimens.insert(std::pair<double, uint64_t>(m_fitnessFunction(intNext), intNext));
		}
	}

	virtual void reducePopulation()
	{
		std::multimap<double, uint64_t>::iterator it = m_specimens.begin();
		for (uint64_t i = 0; i < m_nSurvivors; ++i) {
			++it;
		}
		m_specimens.erase(it, m_specimens.end());
	}

	virtual void learn()
	{
		for (auto &specimen : m_specimens) {
			std::bitset<64> bs(specimen.second);
			for (uint64_t i = 0; i < 64; ++i) {
				m_bitProbability[i] += m_learningRate * (static_cast<double>(bs[i]) - m_bitProbability[i]);
			}
		}
	}

	virtual void evolve() {
		for (uint64_t i = 0; i < m_nIterations; ++i) {
			double bestFitness = (m_specimens.begin())->first;
			generateNextGen();
			reducePopulation();
			learn();
			if (bestFitness >(m_specimens.begin())->first) {
				bestFitness = (m_specimens.begin())->first;
				//std::cout << "new best result at: " << std::setprecision(15) << doubleValue((m_specimens.begin())->second)
				//	<< " with fitness value of: " << bestFitness << std::endl;
			}
		}
		std::cout << std::setprecision(15) << m_specimens.begin()->first << std::endl;
	}

protected:
	std::vector<double> m_bitProbability;
	std::multimap<double, uint64_t> m_specimens;
	double m_learningRate;
	uint64_t m_nIterations, m_nextGenSize, m_nSurvivors;

	std::pair<double, double> m_bounds;
	std::function<double(double)> m_function;

	double m_fitnessFunction(uint64_t value) const { return m_function(doubleValue(value)); }
	double doubleValue(uint64_t value) const
	{
		return m_bounds.first + (m_bounds.second - m_bounds.first) * static_cast<double>(value) / static_cast<double>(std::numeric_limits<uint64_t>::max());
	}
};
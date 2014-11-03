#pragma once

#include "Species.h"

struct CityPositions {
	CityPositions(std::vector<std::pair<double, double>> places) : places(places) {}
	std::vector<std::pair<double, double>> places;
};

class Salesman : public Specimen < std::vector<uint64_t> > {
public:
	Salesman(double mutationRate, std::vector<uint64_t> value, std::shared_ptr<CityPositions> positions)
		: Specimen(mutationRate, value), m_positionsPtr(positions)
	{
		m_fitness = m_fitnessFunction();
	}
	virtual std::string value() const override {
		std::stringstream ss;
		for (auto v : m_value) {
			ss << v << ",";
		}
		return ss.str();
	}
	std::vector<uint64_t> vectValue() const {
		return m_value;
	}
	double fitness() const { return m_fitness; }
	Salesman mutate() const {
		std::vector<uint64_t> newValue = m_value;
		uint64_t size = newValue.size();
		for (uint64_t i = 0; i < size; ++i) {
			for (uint64_t j = 0; j < size; ++j) {
				if (utils::random::decide(m_mutationRate)) {
					std::swap(newValue[i], newValue[j]);
				}
			}
		}
		return Salesman(m_mutationRate, newValue, m_positionsPtr);
	}
	/*Bandit reproduce(Bandit mate) const {
		std::vector<uint64_t> newValue = m_value;
		for (int i = 0; i < m_value.size(); ++i) {
			if (utils::decide(0.5)) {
				newValue[i] = mate.vectValue()[i];
			}
		}
		return Bandit(m_mutationRate, newValue, m_nBandits, m_items);
	}*/

protected:
	std::shared_ptr<CityPositions> m_positionsPtr;

	double m_distance(std::pair<double, double> firstPoint, std::pair<double, double> secondPoint) {
		return sqrt(pow((firstPoint.first - secondPoint.first), 2) + pow((firstPoint.second - secondPoint.second), 2));
	}

	double m_fitnessFunction() {
		double result = 0.0;
		uint64_t size = m_value.size();
		for (uint64_t i = 0; i < m_value.size(); ++i) {
			result += m_distance(m_positionsPtr->places[m_value[i%size]], m_positionsPtr->places[m_value[(i+1)%size]]);
		}
		return result;
	}
};
#pragma once

#include "Species.h"

struct Items {
	Items(std::vector<uint64_t> items, uint64_t total) : itemValues(items), totalValue(total) {}
	std::vector<uint64_t> itemValues;
	uint64_t totalValue;
};

class Bandit : public Specimen < std::vector<uint64_t> > {
public:
	Bandit(double mutationRate, std::vector<uint64_t> value, uint64_t nBandits, std::shared_ptr<Items> items)
		: Specimen(mutationRate, value), m_nBandits(nBandits), m_items(items)
	{
		m_fitness = m_fitnessFunction();
	}
	virtual std::string value() const override {
		return "";
	}
	std::vector<uint64_t> vectValue() const {
		return m_value;
	}
	double fitness() const { return m_fitness; }
	Bandit mutate() const {
		std::vector<uint64_t> newValue = m_value;
		for (auto &owner : newValue) {
			if (mersenneTwister() < m_mutationRate*std::numeric_limits<uint64_t>::max()) {
				owner = mersenneTwister() % m_nBandits;
			}
		}
		return Bandit(m_mutationRate, newValue, m_nBandits, m_items);
	}
	Bandit reproduce(Bandit mate) const {
		std::vector<uint64_t> newValue = m_value;
		for (int i = 0; i < m_value.size(); ++i) {
			if (mersenneTwister() < 0.5*std::numeric_limits<uint64_t>::max()) {
				newValue[i] = mate.vectValue()[i];
			}
		}
		return Bandit(m_mutationRate, newValue, m_nBandits, m_items);
	}

protected:
	std::shared_ptr<Items> m_items;
	uint64_t m_nBandits;

	double m_fitnessFunction() {
		std::vector<uint64_t> part(m_nBandits, 0);
		double result = 0.0;
		for (uint64_t i = 0; i < m_value.size(); ++i) {
			part[m_value[i]] += m_items->itemValues[i];
		}
		double avgValue = static_cast<double>(m_items->totalValue) / m_nBandits;
		for (auto &value : part) {
			result += (value - avgValue)*(value - avgValue);
		}
		return result;
	}
};
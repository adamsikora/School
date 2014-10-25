#pragma once

#include "Species.h"

class CurveValue : public Specimen < uint64_t > {
public:
	CurveValue(double mutationRate, uint64_t value, std::pair<double, double> bounds, std::function<double(double)> function)
		: Specimen(mutationRate, value), m_bounds(bounds), m_function(function)
	{
		m_fitness = m_fitnessFunction();
	}
	virtual std::string value() const override
	{
		std::stringstream ss;
		ss << std::setprecision(5) << doubleValue();
		return ss.str();
	}
	CurveValue mutate() const {
		uint64_t  gray(binToGray(m_value));
		std::bitset<8 * sizeof(uint64_t)> bs(gray);
		for (uint64_t i = 0; i < 8 * sizeof(uint64_t); ++i) {
			if (utils::decide(m_mutationRate)) {
				bs.flip(i);
			}
		}
		gray = bs.to_ullong();
		return CurveValue(m_mutationRate, grayToBin(gray), m_bounds, m_function);
	} 
	CurveValue reproduce(CurveValue mate) const { return CurveValue(*this); }
	
protected:
	std::pair<double, double> m_bounds;
	std::function<double(double)> m_function;

	virtual double m_fitnessFunction() override { return m_function(doubleValue()); }
	double doubleValue() const
	{
		return m_bounds.first + (m_bounds.second - m_bounds.first) * static_cast<double>(m_value) / static_cast<double>(std::numeric_limits<uint64_t>::max());
	}
};
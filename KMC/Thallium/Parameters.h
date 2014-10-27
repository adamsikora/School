#pragma once

#include "StlBase.h"

class ParametersInternal     // class for storing simulation parameters
{
public:
	ParametersInternal() :
		nu(0), T(0), E_M_M(0.0), E_M_Si(0.0), E_M_Tl(0.0), E_bM(0.0), E_b100(0.0), E_b111(0.0),
		layersPerSec(0), targetCoverage(0.0), seed(0) {}
	ParametersInternal
		(
		double nu, double T, double E_M_M, double E_M_Si, double E_M_Tl, double E_bM, double E_b100, double E_b111,
		double layersPerSec, double targetCoverage, int seed
		) :
		nu(nu), T(T), E_M_M(E_M_M), E_M_Si(E_M_Si), E_M_Tl(E_M_Tl), E_bM(E_bM), E_b100(E_b100), E_b111(E_b111),
		initialHeight(initialHeight), layersPerSec(layersPerSec), targetCoverage(targetCoverage), heatingRate(heatingRate), seed(seed) {}

	double nu, T;

	double E_M_M, E_M_Si, E_M_Tl, E_bM, E_b100, E_b111;

	int initialHeight;
	double layersPerSec, targetCoverage, heatingRate;

	int seed;

};

class Parameters {
public:
	void set(std::string parameterName, double parameterValue)
	{
		m_parameters[parameterName] = parameterValue;
	}
	void set(std::pair<std::string, double> pair)
	{
		m_parameters[pair.first] = pair.second;
	}
	double get(std::string parameterName) const
	{
		if (!m_parameters.count(parameterName)) {
			std::cout << "There is no parameter with name " << parameterName << std::endl;
		}
		return m_parameters.find(parameterName)->second;
	}
	std::map<std::string, double> getAll() const
	{
		return m_parameters;
	}
private:
	std::map<std::string, double> m_parameters;
};

class Results {
public:
	void set(std::string parameterName, double parameterValue)
	{
		m_parameters[parameterName] = parameterValue;
	}
	void set(std::pair<std::string, double> pair)
	{
		m_parameters[pair.first] = pair.second;
	}
	double get(std::string parameterName) const
	{
		if (!m_parameters.count(parameterName)) {
			std::cout << "There is no result with name " << parameterName << std::endl;
		}
		return m_parameters.find(parameterName)->second;
	}
	std::map<std::string, double> getAll()
	{
		return m_parameters;
	}
private:
	std::map<std::string, double> m_parameters;
};
#pragma once

#include "Includes.h"
#include "Grid.h"
#include "Parameters.h"

class State {
public:
	State(Parameters para, Results result, const std::vector<uint64_t>& grid);
	State(std::string filename);
	void alterState(Parameters para, Results result, const Grid& grid);
	void loadState(std::string file);
	void saveState(std::string file);

	Parameters getParameters() const { return parameters; }
	double getParameter(std::string parameterName) const { return parameters.get(parameterName); }
	double getResult(std::string parameterName) const { return results.get(parameterName); }
	const std::vector<uint64_t>& getLattice() const { return lattice; }

private:
	Parameters parameters;
	Results results;
	int64_t width, height;
	std::vector<uint64_t> lattice;

};
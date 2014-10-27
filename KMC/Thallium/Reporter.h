#pragma once

#include "State.h"

class Reporter {
public:
	Reporter(State initialState, std::string name = "results") : m_initialState(initialState), m_name(name), m_index(0) {}

	void addState(State state);

	void showInMatlab(const State& state) const;
	void pdbPut(const State& state, std::string name, bool fitToRectangle = true) const;

	void printAllResults();
private:
	std::vector<State> m_states;
	State m_initialState;

	std::string m_name;
	uint64_t m_index;
};
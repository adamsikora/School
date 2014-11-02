#include "State.h"

namespace {
	const std::string stateExtension = ".state";
	const std::string parametersHead = "Simulation Parameters:";
	const std::string resultsHead = "Simulation Results:";
	const std::string gridHead = "Lattice:";
	const std::string latticeDimensionsHead = "Lattice Dimensions:";
	const std::string latticeWidth = "Lattice Width";
	const std::string latticeHeight = "Lattice Height";
	const std::string equals = " = ";
	const std::string endLine = "\n";

	std::pair<std::string, double> decodeLine(std::string line)
	{
		size_t position = line.find('=');
		std::string name = line.substr(0, position);
		while (name.back() == ' ') { name.pop_back(); }
		std::stringstream ss;
		ss << line.substr(position + 1);
		double value = 0.0;
		ss >> value;

		return std::pair<std::string, double>(name, value);
	}
}

State::State(Parameters para, Results result, const std::vector<uint64_t>& grid)
	: parameters(para), results(result), lattice(grid), width(c::w), height(c::h)
{

}

State::State(std::string filename) : lattice(c::A, 0), width(c::w), height(c::h)
{
	loadState(filename);
}

void State::alterState(Parameters para, Results result, const Grid& grid)
{
	parameters = para;
	results = result;
	for (int i = 0; i < c::A; ++i) {
		lattice[i] = grid.present(i);
	}
}


void State::loadState(std::string fileName)
{
	enum readingState {
		unknown, rparameters, rresults, rlatticeDimensions, rgrid
	};
	readingState state = readingState::unknown;

	std::ifstream file(fileName + stateExtension);

	if (!file.is_open()) {
		std::cout << "failed to read state file\n";
	}

	const uint64_t bufferSize = 1024;
	char buffer[bufferSize];
	uint64_t gridPosition = 0;

	while (file.getline(buffer, bufferSize)) {
		std::string line = buffer;
		if (line == "") {
			continue;
		}
		else if (line == parametersHead) {
			state = readingState::rparameters;
		}
		else if (line == resultsHead) {
			state = readingState::rresults;
		}
		else if (line == latticeDimensionsHead) {
			state = readingState::rlatticeDimensions;
		}
		else if (line == gridHead) {
			state = readingState::rgrid;
		}
		else {
			switch (state) {
			case readingState::rparameters: {
				parameters.set(decodeLine(line));
				break;
			}
			case readingState::rlatticeDimensions: {
				std::pair<std::string, double> ld = decodeLine(line);
				if (ld.first == latticeWidth && ld.second != width) {
					std::cout << "wrong lattice width in state file" << endLine;
				}
				if (ld.first == latticeHeight && ld.second != height) {
					std::cout << "wrong lattice height in state file" << endLine;
				}
				break;
			}
			case readingState::rresults: {
				results.set(decodeLine(line));
				break;
			}
			case readingState::rgrid: {
				std::stringstream ss;
				ss << line;
				uint64_t current = 0, count = 0;
				ss >> count;
				if (count == 0) {
					std::cout << "wrong grid format in state file" << endLine;
				}
				ss >> current;
				for (uint64_t i = 0; i < count; ++i, ++gridPosition) {
					lattice[gridPosition] = current;
				}
				break;
			}
			default: {
				break;
			}
			}
		}
	}
	if (!(gridPosition == c::A || gridPosition == 0)) {
		std::cout << "wrong grid dimensions in state file";
	}

	file.close();
}

void State::saveState(std::string fileName)
{
	std::ofstream file(fileName + stateExtension);

	if (!file.is_open()) {
		std::cout << "failed to write to state file\n";
	}

	file << endLine << parametersHead << endLine << endLine;

	for (auto &parameter : parameters.getAll()) {
		file << parameter.first << equals << parameter.second << endLine;
	}

	file << endLine << latticeDimensionsHead << endLine << endLine;

	file << latticeWidth << equals << width << endLine;
	file << latticeHeight << equals << height << endLine;

	file << endLine << resultsHead << endLine << endLine;

	for (auto &result : results.getAll()) {
		file << result.first << equals << result.second << endLine;
	}

	file << endLine << gridHead << endLine << endLine;

	uint64_t current = lattice[0];		// lattice encoded by chunks of same value
	uint64_t count = 1;
	for (uint64_t i = 1; i < width * height; ++i) {
		if (lattice[i] == current) {
			++count;
		}
		else {
			file << count << " " << current << endLine;
			current = lattice[i];
			count = 1;
		}
	}
	file << count << " " << current << endLine;

	file.close();
}
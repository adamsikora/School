#include "Includes.h"
#include "Input.h"
#include "Results.h"
#include "Grid.h"

namespace next {
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
		double get(std::string parameterName)
		{
			if (!m_parameters.count(parameterName)) {
				std::cout << "There is no parameter with name " << parameterName << std::endl;
			}
			return m_parameters[parameterName];
		}
		std::map<std::string, double> getAll()
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
		double get(std::string parameterName)
		{
			if (!m_parameters.count(parameterName)) {
				std::cout << "There is no parameter with name " << parameterName << std::endl;
			}
			return m_parameters[parameterName];
		}
		std::map<std::string, double> getAll()
		{
			return m_parameters;
		}
	private:
		std::map<std::string, double> m_parameters;
	};
}

class State {
public:
	State(next::Parameters para, next::Results result, const std::vector<uint64_t>& grid);
	State(std::string filename);
	void alterState(next::Parameters para, next::Results result, const Grid& grid);
	void loadState(std::string file);
	void saveState(std::string file);

private:
	next::Parameters parameters;
	next::Results results;
	int64_t width, height;
	std::vector<uint64_t> lattice;

};
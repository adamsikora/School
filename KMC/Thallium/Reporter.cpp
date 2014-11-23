#include "Reporter.h"

#include "MatlabEngine.h"

namespace {
	std::string pdbExtension = ".pdb";
}

void Reporter::addState(State state)
{
	m_states.push_back(state);
	std::stringstream ss;
	ss << m_name << m_index++;
	state.saveState(ss.str());
	pdbPut(state, ss.str());
	
	showInMatlab(state);
}

void Reporter::showInMatlab(const State& state) const
{
	std::vector<double> toshow(c::A, 0.0);
	const std::vector<uint64_t>& lattice = state.getLattice();

	for (uint64_t j = 0; j < c::h; ++j) {
		for (uint64_t i = 0; i < c::w; ++i) {
			toshow[c::w * j + (i + j / 2) % c::w] = lattice[i + c::w * j];
		}
	}

	utils::matlab::draw(toshow, std::pair<uint64_t, uint64_t>(c::w, c::h));
}

void Reporter::pdbPut(const State& state, std::string name, bool fitToRectangle) const
{

	std::ofstream file(name + pdbExtension);

	const std::vector<uint64_t>& lattice = state.getLattice();

	file << std::fixed;

	double dist = 3.450;
	int line = 1;
	double x, y, z, t;
	for (int pi = 0; pi < c::h; pi++) {
		for (int pj = 0; pj < c::w; pj++) {
			x = dist*(pj + 0.5*(pi - 1));
			y = -sqrt(3.0) / 2.0*dist*(pi + 1.0 / 3.0*(-1));
			z = sqrt(2.0 / 3.0)*dist*(-1);
			t = 0.1 * 0;
	
			if (fitToRectangle) {
				if ((pi + 1) / 2 + pj > c::w - 1) {
					x -= c::w * dist - 0.5 * dist;
					y -= sqrt(3.0) / 2.0 * dist;
				}
			}
			file << "ATOM  "
				<< std::setw(5) << line++ << " Tl   UNK     0    "
				<< std::setw(8) << std::setprecision(3) << x
				<< std::setw(8) << std::setprecision(3) << y
				<< std::setw(8) << std::setprecision(3) << z
				<< std::setw(6) << std::setprecision(2) << 0.0
				<< std::setw(6) << std::setprecision(2) << t
				<< "  0" << "\n";
		}
	}

	for (int pi = 0; pi < c::h; pi++) {
		for (int pj = 0; pj < c::w; pj++) {
			if (lattice[pi * c::w + pj] != atomType::nothing) {
				x = dist*(pj + 0.5*pi);
				y = -sqrt(3.0) / 2.0*dist*pi;
				z = 0.0;
				t = lattice[pi * c::w + pj];

				if (fitToRectangle) {
					if ((pi + 1) / 2 + pj > c::w - 1) {
						x -= c::w * dist - 0.5 * dist;
						y -= sqrt(3.0) / 2.0 * dist;
					}
				}
				file << "ATOM  "
					<< std::setw(5) << line++ << (lattice[pi * c::w + pj] == atomType::metal ? " Mn" : " Si") << "   UNK     0    "
					<< std::setw(8) << std::setprecision(3) << x
					<< std::setw(8) << std::setprecision(3) << y
					<< std::setw(8) << std::setprecision(3) << z
					<< std::setw(6) << std::setprecision(2) << 0.0
					<< std::setw(6) << std::setprecision(2) << t
					<< "  0" << "\n";
			}
		}
	}
	file.close();
}
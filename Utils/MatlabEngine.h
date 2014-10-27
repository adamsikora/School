#pragma once

#include "StlBase.h"

namespace utils
{
	namespace matlab
	{
		void plot(const std::vector<std::pair<double, double>>& data);
		void draw(const std::vector<double>& data, std::pair<uint64_t, uint64_t> range, std::string colormap = "jet");
		void draw(const std::vector<uint64_t>& data, std::pair<uint64_t, uint64_t> range, std::string colormap = "jet");
		void evaluate(std::string command);
	}
}
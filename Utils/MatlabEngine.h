#pragma once

#include "StlBase.h"

namespace utils
{
	namespace matlab
	{
		void plot(const std::vector<std::pair<double, double>>& data);
		void show();
		void evaluate(std::string command);
	}
}
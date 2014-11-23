#include "StlBase.h"
#include "StopWatch.h"
#include "MatlabEngine.h"

//const double A0 = 1e10;
//const double k = 1e-7;
//const double step = 1e-8;

std::vector<double> mass = { 1.989e30, 5.972e24, 7.348e22 };
std::vector<std::pair<double, double>> position = { { 0.0, 0.0 }, { 0.0, 147.09e9 }, { 0.0, 147.09e9 + 0.3633e9 } };
std::vector<std::pair<double, double>> velocity = { { 9.21e-2, 0.0 }, { -30.29e3, 0.0 }, { -(30.29e3 + 1.076e3), 0.0 } };
std::pair<double, double> force[3][3];

std::vector<std::pair<double, double>> energies;

const double cappa = 6.67384e-11;
const double deltat = 1e5;
double t = 0.0;
double year = 3.15569e7;

std::pair<double, double> getForce(int i, int j) {
  if (i > j) {
    return std::pair<double, double>(-force[j][i].first, -force[j][i].second);
  } else {
    return force[i][j];
  }
}

void move() {
  for (int i = 0; i < 3; ++i) {
    position[i].first += deltat * velocity[i].first;
    position[i].second += deltat * velocity[i].second;
  }
  for (int i = 0; i < 2; ++i) {
    for (int j = i + 1; j < 3; ++j) {
      std::pair<double, double> r = std::pair<double, double>(position[j].first - position[i].first, position[j].second - position[i].second);
      double rlength = sqrt(r.first*r.first + r.second*r.second);
      double inter = cappa * mass[i] * mass[j] / pow(rlength, 3);
      force[i][j] = std::pair<double, double>(r.first*inter, r.second*inter);
    }
  }
  velocity[0].first += deltat * (getForce(0, 1).first + getForce(0, 2).first) / mass[0];
  velocity[0].second += deltat * (getForce(0, 1).second + getForce(0, 2).second) / mass[0];
  velocity[1].first += deltat * (getForce(1, 0).first + getForce(1, 2).first) / mass[1];
  velocity[1].second += deltat * (getForce(1, 0).second + getForce(1, 2).second) / mass[1];
  velocity[2].first += deltat * (getForce(2, 1).first + getForce(2, 0).first) / mass[2];
  velocity[2].second += deltat * (getForce(2, 1).second + getForce(2, 0).second) / mass[2];
  t += deltat;
}

double calculateEnergy() {
  double result = 0.0;
  for (int i = 0; i < 3; ++i) {
    result += 1.0 / 2.0 * mass[i] * sqrt(velocity[i].first*velocity[i].first + velocity[i].second*velocity[i].second);
  }
  /*for (int i = 0; i < 2; ++i) {
    for (int j = i + 1; j < 3; ++j) {
      std::pair<double, double> r = std::pair<double, double>(position[j].first - position[i].first, position[j].second - position[i].second);
      double rlength = sqrt(r.first*r.first + r.second*r.second);
      result -= cappa * mass[i] * mass[j] / rlength;
    }
  }*/
  return result;
}

int main() {
  std::vector<std::pair<double, double>> tr;
  while (t < 10 * year) {
    move();
    energies.emplace_back(t, calculateEnergy());
    tr.emplace_back(position[0]);
  }
  utils::matlab::plot(energies);
  //std::vector<std::pair<double, double>> vec, topl;
  //for (double x = -5; x <= 5; x += 0.1) {
  //  vec.emplace_back(x, sin(x));
  //}
  //utils::matlab::plot(vec);
  
  //vec.emplace_back(0.0, A0); topl.emplace_back(0.0, 0.0);
  /*for (double t = step; t < 0.1; t += step) {
    double trueValue = 1.0 / (1.0 / A0 + k*t);
    double newValue = vec.back().second - step*k*pow(vec.back().second, 2);
    vec.emplace_back(t, newValue);
    topl.emplace_back(t, (trueValue - newValue) / newValue);
  }*/
  /*for (double t = step; t < 0.1; t += step) {
	double trueValue = 1.0 / (1.0 / A0 + k*t);
	double oldValue = vec.back().second;
	double d1 = -step * k*pow(oldValue, 2);
	double d2 = -step * k*pow(oldValue + d1 / 2.0, 2);
	double d3 = -step * k*pow(oldValue + d2 / 2.0, 2);
	double d4 = -step * k*pow(oldValue + d3, 2);
	double newValue = oldValue + (d1+2*d2+2*d3+d3)/6.0;
	vec.emplace_back(t, newValue);
	topl.emplace_back(t, (trueValue - newValue) / newValue);
  }*/
  std::cin.ignore();

  return 0;
}
#include "StlBase.h"
#include "StopWatch.h"
#include "RandomUtils.h"
#include "MatlabEngine.h"

int main() {

  std::vector<double> voltages = {-12.46,-10.66, -8.67, -6.49, -4.51, -2.73, -0.99, 0};

  std::vector<std::vector<std::pair<double, double>>> allData;
  
  for (double &voltage : voltages) {
    std::stringstream ss;
    ss << voltage << ".asc";
    std::ifstream file(ss.str().c_str(), std::ios_base::in);
    if (!file.good() || !file.is_open()) {
      std::cout << "badfile\n";
    }

    std::string line;
    file >> line;
    while (line != "ScanData") {
      file >> line;
    }
    file >> line;
    std::cout << line;

    std::vector<std::pair<double, double>> datas;
    while (file.good()) {
      double f, s;
      file >> f;
      file >> s;
      datas.emplace_back(f, s);
    }
    std::vector<std::pair<double, double>> clear;
    double curr = 0.0;
    double sum = 0.0;
    int count = 0;
    for (auto &dat : datas) {
      if (dat.first < curr + 0.1 && dat.first > curr - 0.1) {
        ++count;
        sum += dat.second;
      }
      if (dat.first > curr + 0.1) {
        clear.emplace_back(curr, sum / count);
        curr += 1.0;
        count = 0;
        sum = 0.0;
      }
    }
    allData.push_back(clear);
    /*while (file.getline(buffer, bufferSize)) {
      std::cout << buffer << std::endl;
      std::string line = buffer;
      if (data) {
        std::stringstream ss2;
        ss2 << line;
        double f, s;
        ss2 >> f;
        ss2 >> s;
        datas.emplace_back(f, s);
      }
      if (line == "ScanData	1") {
        data = true;
      }
    }*/
  }
  for (int i = 0; i < allData.size(); ++i) {
    utils::matlab::plot(allData[i]);
  }
  std::ofstream output("eid.txt");
  for (int i = 0; i < 8; ++i) {
    output << voltages[i] << "\t";
    for (int j = 0; j < 40; ++j) {
      output << allData[i][j].second << "\t";
    }
    output << "\n";
  }


  std::cin.ignore();

  return 0;
}
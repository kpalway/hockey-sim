#include "CSV.hpp"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

std::vector< std::vector<std::string> > CSV::ToMatrix(std::string filename) {
  std::ifstream ifs(filename);

  if (!ifs.good()) {
    std::cerr << "Error reading file " << filename << std::endl;
    exit(1);
  }

  std::vector< std::vector<std::string> > res;
  char rowc[5000];
  while (!ifs.eof()) {
    ifs.getline(rowc, 4999);
    std::string row(rowc);
    std::vector<std::string> cells;
    boost::split(cells, row, boost::is_any_of(","));
    for (unsigned int i = 0; i < cells.size(); i++) {
      cells[i] = cells[i].substr(1, cells[i].length() - 2);
    }
    res.push_back(cells);
  }
  return res;
}

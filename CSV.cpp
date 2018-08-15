#include "CSV.hpp"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>

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
    if (row.length() == 0) {
      break;
    }
    // remove line breaks or trailing space
    row.erase(row.find_last_not_of(" \n\r\t") + 1);

    // evidently we need to repalce unicode non-breaking spaces in the NatStatTrick files..
    boost::replace_all(row, "\302\240", " ");
    boost::replace_all(row, "\240", " ");

    std::vector<std::string> cells;
    boost::split(cells, row, boost::is_any_of(","));
    for (uint i = 0; i < cells.size(); i++) {
      if (cells[i].length() > 0 && cells[i][0] == '\"') {
        cells[i] = cells[i].substr(1, cells[i].length() - 2);
      }
    }
    res.push_back(cells);
  }
  return res;
}

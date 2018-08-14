#include <vector>
#include <string>

#ifndef CSV_HPP
#define CSV_HPP

namespace CSV {
  std::vector< std::vector<std::string> > ToMatrix(std::string filename);
};

#endif // CSV_HPP

#include <vector>
#include <string>

#ifndef STATS_HPP
#define STATS_HPP

class Stats {
  virtual void loadData(std::vector<std::string> &data) = 0;
};

#endif // STATS_HPP

#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>
#include "PlayerDatabase.hpp"
#include "TeamDatabase.hpp"

class Season;

class Simulator {
public:
  Simulator(PlayerDatabase &pdb, TeamDatabase &tdb): pdb(pdb), tdb(tdb) { }
  void SimulateGame(std::string home, std::string away, uint iters);
  void SimulateSeason(Season &season, int iterations);
private:
  PlayerDatabase &pdb;
  TeamDatabase &tdb;
};

#endif // SIMULATOR_HPP

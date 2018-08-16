#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>
#include <random>
#include "PlayerDatabase.hpp"
#include "TeamDatabase.hpp"

class Simulator {
public:
  Simulator(std::default_random_engine &RNG, PlayerDatabase &pdb, TeamDatabase &tdb): RNG(RNG), pdb(pdb), tdb(tdb) { }
  void SimulateGame(std::string home, std::string away, uint iters);
private:
  std::default_random_engine &RNG;
  PlayerDatabase &pdb;
  TeamDatabase &tdb;
};

#endif // SIMULATOR_HPP

#include <iostream>
#include <random>
#include <chrono>
#include "PlayerDatabase.hpp"
#include "TeamDatabase.hpp"
#include "Simulator.hpp"

int main() {
  std::default_random_engine RNG(std::chrono::system_clock::now().time_since_epoch().count());

  PlayerDatabase pdb;
  pdb.initialize();
  Replacement repl(pdb);
  repl.initialize();
  TeamDatabase tdb;
  tdb.initialize(pdb);

  pdb.PredictAll(repl);

  Simulator sim(RNG, pdb, tdb);

  sim.SimulateGame("TOR", "BOS", 7);
}

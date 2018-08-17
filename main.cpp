#include <iostream>
#include <random>
#include <chrono>
#include "PlayerDatabase.hpp"
#include "TeamDatabase.hpp"
#include "Simulator.hpp"

int main(int argc, char *argv[]) {
  std::default_random_engine RNG(std::chrono::system_clock::now().time_since_epoch().count());

  PlayerDatabase pdb;
  pdb.initialize();
  Replacement repl(pdb);
  repl.initialize();
  TeamDatabase tdb;
  tdb.initialize(pdb);

  pdb.PredictAll(repl);

  Simulator sim(RNG, pdb, tdb);

  if (argc < 3) {
    std::cerr << "Invalid command line arguments" << std::endl;
    exit(1);
  }

  std::string home(argv[1]);
  std::string away(argv[2]);
  uint games = 7;
  if (argc == 4) {
    games = std::stoi(argv[3]);
  }

  sim.SimulateGame(home, away, games);
  pdb.PrintIndividualStats();
}

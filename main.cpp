#include <iostream>
#include "PlayerDatabase.hpp"
#include "TeamDatabase.hpp"
#include "Simulator.hpp"
#include "Season.hpp"
#include "Probability.hpp"

int main(int argc, char *argv[]) {
  Probability::initialize();

  PlayerDatabase pdb;
  pdb.initialize();
  Replacement repl(pdb);
  repl.initialize();
  TeamDatabase tdb;
  tdb.initialize(pdb);

  pdb.PredictAll(repl);

  Simulator sim(pdb, tdb);

  if (argc < 3) {
    std::cout << "Simulating full season" << std::endl;

    Season season("18-19");
    season.loadSeason();
    int iters = 10;
    if (argc == 2) {
      std::string iters_str(argv[1]);
      iters = std::stoi(iters_str);
    }
    sim.SimulateSeason(season, iters);
    pdb.PrintIndividualStats();
  }
  else {
    std::string home(argv[1]);
    std::string away(argv[2]);
    uint games = 7;
    if (argc == 4) {
      games = std::stoi(argv[3]);
    }

    sim.SimulateGame(home, away, games);
  }
}

#include <iostream>
#include "Simulator.hpp"
#include "Game.hpp"

void Simulator::SimulateGame(std::string home, std::string away, uint iters) {
  Team &home_team = tdb.lookup(home);
  Team &away_team = tdb.lookup(away);
  int home_wins = 0;
  int ties = 0;
  int away_wins = 0;
  for (uint i = 0; i < iters; i++) {
    Game game(RNG, home_team, away_team);
    if (game.Ready()) {
      game.Simulate();
      if (game.HomeWins()) {
        home_wins++;
      }
      else if (game.Tied()) {
        ties++;
      }
      else {
        away_wins++;
      }
      if (iters < 10) {
        game.PrintBoxScore();
        std::cout << "----------" << std::endl;
      }
    }
    else {
      std::cerr << "Game not ready." << std::endl;
    }
  }
  if (iters >= 10) {
    double home_pct = 100*((double)home_wins)/iters;
    double tie_pct = 100*((double)ties)/iters;
    double away_pct = 100*((double)away_wins)/iters;
    std::cout << home << " " << home_pct << "%, tie " << tie_pct << "%, " << away << " " << away_pct << "%" << std::endl;
  }
  else {
    std::cout << home << " " << home_wins << " wins, " << ties << " ties, " << away << " " << away_wins << " wins" << std::endl;
  }
}

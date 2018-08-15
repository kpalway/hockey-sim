#include <iostream>
#include <random>
#include <chrono>
#include "PlayerDatabase.hpp"
#include "TeamDatabase.hpp"
#include "Game.hpp"

int main() {
  std::default_random_engine RNG(std::chrono::system_clock::now().time_since_epoch().count());

  PlayerDatabase pdb;
  pdb.initialize();
  TeamDatabase tdb;
  tdb.initialize(pdb);

  pdb.PredictAll();

  Team &TOR = tdb.lookup("TOR");
  Team &BOS = tdb.lookup("BOS");
  int TORwins = 0;
  int ties = 0;
  int BOSwins = 0;
  const int sims = 5000;
  for (int i = 0; i < sims; i++) {
    Game game(RNG, TOR, BOS);
    if (game.Ready()) {
      game.Simulate();
      if (game.HomeWins()) {
        TORwins++;
      }
      else if (game.Tied()) {
        ties++;
      }
      else {
        BOSwins++;
      }
    }
    else {
      std::cerr << "Game not ready." << std::endl;
    }
  }
  double TORpct = 100*((double)TORwins)/sims;
  double TIEpct = 100*((double)ties)/sims ;
  double BOSpct = 100*((double)BOSwins)/sims;
  std::cout << "TOR " << TORpct << "%, tie " << TIEpct << "%, BOS " << BOSpct << "%" << std::endl;
}

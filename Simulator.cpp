#include <iostream>
#include "Simulator.hpp"
#include "Game.hpp"
#include "Season.hpp"

void Simulator::SimulateGame(std::string home, std::string away, uint iters) {
  Team &home_team = tdb.lookup(home);
  Team &away_team = tdb.lookup(away);
  int home_wins = 0;
  int ties = 0;
  int away_wins = 0;
  for (uint i = 0; i < iters; i++) {
    Game game(home_team, away_team);
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

void Simulator::SimulateSeason(Season &season) {
  Date date = season.StartDate();
  Date end_date = season.EndDate();

  while (date <= end_date) {
    Schedule today = season.DaySchedule(date);

    for (uint i = 0; i < today.size(); i++) {
      Team &home_team = tdb.lookup(std::get<1>(today[i]));
      Team &away_team = tdb.lookup(std::get<2>(today[i]));
      Game game(home_team, away_team);
      if (game.Ready()) {
        game.Simulate();
      }
      else {
        std::cerr << "Game not ready." << std::endl;
      }
    }
    date.AddDay();
    pdb.PassDay();
  }
}

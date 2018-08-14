#include "Game.hpp"
#include "PeriodEnd.hpp"

Game::~Game() {
  for (uint i = 0; i < game_log.size(); i++) {
    delete game_log[i];
  }
}

void Game::Simulate() {
  period = 1;
  time = 0;
  home_goals = 0;
  away_goals = 0;

  while (!simulated) {
    DrawNextEvent();
    game_log[game_log.size() - 1]->apply();
  }
}

bool Game::IsHome(std::string &team) {
  return 0 == team.compare(home_team.Name());
}

void Game::AddGoal(std::string team) {
  if (IsHome(team)) {
    home_goals++;
  }
  else {
    away_goals++;
  }
}

void Game::SetActiveLine(std::string team, Player *LW, Player *C, Player *RW, Player *LD, Player *RD) {
  if (IsHome(team)) {
    home_LW = LW;
    home_C = C;
    home_RW = RW;
    home_LD = LD;
    home_RD = RD;
  }
  else {
    away_LW = LW;
    away_C = C;
    away_RW = RW;
    away_LD = LD;
    away_RD = RD;
  }
}

void Game::SetTime(double time) {
  this->time = time;
}

void Game::NextPeriod() {
  if (period == 3) {
    simulated = true;
  }
  else {
    period++;
  }
}

void Game::DrawNextEvent() {
  // TODO
  PeriodEnd *pe = new PeriodEnd(*this, period);
  game_log.push_back(pe);
}

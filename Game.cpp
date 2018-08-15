#include <algorithm>
#include "Game.hpp"
#include "ShotAttempt.hpp"
#include "Shot.hpp"
#include "Goal.hpp"
#include "PeriodEnd.hpp"
#include "LineChange.hpp"

#define PROB_ASSIST1 0.85
#define PROB_ASSIST2 0.85

Game::~Game() {
  for (uint i = 0; i < game_log.size(); i++) {
    delete game_log[i];
  }
}

bool Game::Ready() {
  return !simulated && home_team.Ready() && away_team.Ready();
}

void Game::Simulate() {
  period = 1;
  time = 0;
  home_shift_remaining = SHIFT_LENGTH;
  away_shift_remaining = SHIFT_LENGTH;
  home_goals = 0;
  away_goals = 0;

  home_LW = home_team.LW[0];
  home_C = home_team.C[0];
  home_RW = home_team.RW[0];
  home_LD = home_team.LD[0];
  home_RD = home_team.RD[0];

  away_LW = away_team.LW[0];
  away_C = away_team.C[0];
  away_RW = away_team.RW[0];
  away_LD = away_team.LD[0];
  away_RD = away_team.RD[0];

  while (!simulated) {
    DrawNextEvent();
    game_log[game_log.size() - 1]->apply();
  }
}

void Game::PrintBoxScore() {
  for (uint i = 0; i < game_log.size(); i++) {
    EventType et = game_log[i]->Type();
    if (et == EventType::GOAL || et == EventType::PERIOD_END || et == EventType::PENALTY) {
      game_log[i]->print();
    }
  }
}

bool Game::HomeWins() {
  return home_goals > away_goals;
}

bool Game::Tied() {
  return home_goals == away_goals;
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
    home_shift_remaining = SHIFT_LENGTH;
  }
  else {
    away_LW = LW;
    away_C = C;
    away_RW = RW;
    away_LD = LD;
    away_RD = RD;
    away_shift_remaining = SHIFT_LENGTH;
  }
}

void Game::SetTime(double time) {
  double diff = time - this->time;
  home_shift_remaining -= diff;
  away_shift_remaining -= diff;
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

double Game::DrawFromExp(double lambda) {
  std::exponential_distribution<double> dist(lambda);
  return dist(RNG);
}

bool Game::TrueWithProbability(double prob) {
  std::uniform_real_distribution<double> dist(0, 1);
  return dist(RNG) <= prob;
}

double Game::DrawFromExps(std::vector<double> &lambdas, uint &min_ind) {
  double min_time = 999999;
  min_ind = 0;
  for (uint i = 0; i < lambdas.size(); i++) {
    double time = DrawFromExp(lambdas[i]);
    if (time < min_time) {
      min_time = time;
      min_ind = i;
    }
  }
  return min_time;
}

Player *Game::ChooseFirstAssist(Player *scorer, bool home) {
  std::vector<Player*> candidates;
  if (home) {
    candidates.push_back(home_LW);
    candidates.push_back(home_C);
    candidates.push_back(home_RW);
    candidates.push_back(home_LD);
    candidates.push_back(home_RD);
  }
  else {
    candidates.push_back(away_LW);
    candidates.push_back(away_C);
    candidates.push_back(away_RW);
    candidates.push_back(away_LD);
    candidates.push_back(away_RD);
  }
  candidates.erase(std::remove(candidates.begin(), candidates.end(), scorer), candidates.end());

  std::vector<double> probs;
  for (uint i = 0; i < candidates.size(); i++) {
    probs.push_back(candidates[i]->FirstAssistsPerOnIceShot());
  }
  
  std::discrete_distribution<int> dist(probs.begin(), probs.end());
  return candidates[dist(RNG)];
}

Player *Game::ChooseSecondAssist(Player *scorer, Player *assist1, bool home) {
  std::vector<Player*> candidates;
  if (home) {
    candidates.push_back(home_LW);
    candidates.push_back(home_C);
    candidates.push_back(home_RW);
    candidates.push_back(home_LD);
    candidates.push_back(home_RD);
  }
  else {
    candidates.push_back(away_LW);
    candidates.push_back(away_C);
    candidates.push_back(away_RW);
    candidates.push_back(away_LD);
    candidates.push_back(away_RD);
  }
  candidates.erase(std::remove(candidates.begin(), candidates.end(), scorer), candidates.end());
  candidates.erase(std::remove(candidates.begin(), candidates.end(), assist1), candidates.end());

  std::vector<double> probs;
  for (uint i = 0; i < candidates.size(); i++) {
    probs.push_back(1);
  }
  
  std::discrete_distribution<int> dist(probs.begin(), probs.end());
  return candidates[dist(RNG)];
}

int Game::SelectFwdLine(bool home) {
  std::vector<double> probs;
  probs.push_back(29);
  probs.push_back(27);
  probs.push_back(24);
  probs.push_back(19);
  std::discrete_distribution<int> dist(probs.begin(), probs.end());
  return dist(RNG);
}

int Game::SelectDefLine(bool home) {
  std::vector<double> probs;
  probs.push_back(23);
  probs.push_back(20);
  probs.push_back(17);
  std::discrete_distribution<int> dist(probs.begin(), probs.end());
  return dist(RNG);
}

void Game::DrawNextEvent() {
  // draw from distribution for each active player's shot attempt rate
  std::vector<double> lambdas;
  lambdas.push_back(home_LW->ShotAttemptsPerMinute());
  lambdas.push_back(home_C->ShotAttemptsPerMinute());
  lambdas.push_back(home_RW->ShotAttemptsPerMinute());
  lambdas.push_back(home_LD->ShotAttemptsPerMinute());
  lambdas.push_back(home_RD->ShotAttemptsPerMinute());
  lambdas.push_back(away_LW->ShotAttemptsPerMinute());
  lambdas.push_back(away_C->ShotAttemptsPerMinute());
  lambdas.push_back(away_RW->ShotAttemptsPerMinute());
  lambdas.push_back(away_LD->ShotAttemptsPerMinute());
  lambdas.push_back(away_RD->ShotAttemptsPerMinute());
  
  uint min_ind;
  double attempt_time = DrawFromExps(lambdas, min_ind);
  
  Player *shooter = NULL;
  bool shooter_home = min_ind <= 4;

  std::string team = away_team.Name();
  if (shooter_home) {
    team = home_team.Name();
  }

  switch (min_ind) {
  case 0:
    shooter = home_LW;
    break;
  case 1:
    shooter = home_C;
    break;
  case 2:
    shooter = home_RW;
    break;
  case 3:
    shooter = home_LD;
    break;
  case 4:
    shooter = home_RD;
    break;
  case 5:
    shooter = away_LW;
    break;
  case 6:
    shooter = away_C;
    break;
  case 7:
    shooter = away_RW;
    break;
  case 8:
    shooter = away_LD;
    break;
  case 9:
    shooter = away_RD;
    break;
  }

  Player *goalie = home_G;
  if (shooter_home) {
    goalie = away_G;
  }

  double period_remaining = 20 - time;

  Event *ev = NULL;

  // need to make a line change
  if (away_shift_remaining <= 0) {
    int fwd_line = SelectFwdLine(false);
    int def_line = SelectDefLine(false);
    ev = new LineChange(*this, period, time, away_team.Name(),
      away_team.LW[fwd_line], away_team.C[fwd_line], away_team.RW[fwd_line],
      away_team.LD[def_line], away_team.RD[def_line]);
  }
  else if (home_shift_remaining <= 0) {
    int fwd_line = SelectFwdLine(true);
    int def_line = SelectDefLine(true);
    ev = new LineChange(*this, period, time, home_team.Name(),
      home_team.LW[fwd_line], home_team.C[fwd_line], home_team.RW[fwd_line],
      home_team.LD[def_line], home_team.RD[def_line]);
  }
  // shot attempt will happen
  else if (attempt_time < period_remaining) {
    // if shot goes on net
    if (TrueWithProbability(shooter->ShotsPerShotAttempt())) {
      double goal_prob = shooter->GoalsPerShot()/(1-goalie->GoalsPerShotAgainst()+shooter->GoalsPerShot());
      // if shot goes in
      if (TrueWithProbability(goal_prob)) {
        Player *assist1 = NULL;
        Player *assist2 = NULL;
        // if there is a first assist
        if (TrueWithProbability(PROB_ASSIST1)) {
          // proportionally decide which player gets the first assist
          assist1 = ChooseFirstAssist(shooter, shooter_home);
          // if there is a second assist
          if (TrueWithProbability(PROB_ASSIST2)) {
            // uniformly decide the second assist
            assist2 = ChooseSecondAssist(shooter, assist1, shooter_home);
          }
        }

        ev = new Goal(*this, period, time + attempt_time, team, shooter, assist1, assist2);
      }
      else {
        ev = new Shot(*this, period, time + attempt_time, shooter, goalie);
      }
    }
    else {
      ev = new ShotAttempt(*this, period, time + attempt_time, shooter);
    }
  }
  // period ends
  else {
    ev = new PeriodEnd(*this, period);
  }

  game_log.push_back(ev);
}

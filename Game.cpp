#include <algorithm>
#include "Game.hpp"
#include "ShotAttempt.hpp"
#include "Shot.hpp"
#include "Goal.hpp"
#include "PeriodEnd.hpp"
#include "LineChange.hpp"
#include "PenaltyEnd.hpp"
#include <iostream>

#define PROB_ASSIST1 0.85
#define PROB_ASSIST2 0.80

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
  home_sit = away_sit = Situation::EV;

  home_team.AddGamePlayed();
  away_team.AddGamePlayed();

  home_LW = home_team.LW[0];
  home_C = home_team.C[0];
  home_RW = home_team.RW[0];
  home_LD = home_team.LD[0];
  home_RD = home_team.RD[0];
  if (home_team.G[0]->Fatigue() == 0) {
    home_G = home_team.G[0];
  }
  else {
    home_G = home_team.G[1];
  }

  away_LW = away_team.LW[0];
  away_C = away_team.C[0];
  away_RW = away_team.RW[0];
  away_LD = away_team.LD[0];
  away_RD = away_team.RD[0];
  if (away_team.G[0]->Fatigue() == 0) {
    away_G = away_team.G[0];
  }
  else {
    away_G = away_team.G[1];
  }

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
  std::cout << "Final: " << home_team.Name() << " " << home_goals << " - " << away_goals << " " << away_team.Name() << std::endl;
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

void Game::AddShotAttempt(std::string team) {
  if (IsHome(team)) {
    AddStat(true, false, false);
  }
  else {
    AddStat(false, false, false);
  }
}

void Game::AddShot(std::string team) {
  if (IsHome(team)) {
    AddStat(true, true, false);
  }
  else {
    AddStat(false, true, false);
  }
}

void Game::AddStat(bool home, bool shot, bool goal) {
  std::vector<Player*> home_active = HomeActive();
  std::vector<Player*> away_active = AwayActive();
  if (home) {
    for (uint i = 0; i < home_active.size(); i++) {
      if (goal) home_active[i]->AddGoalFor(home_sit);
      if (shot) home_active[i]->AddShotFor(home_sit);
      home_active[i]->AddShotAttemptFor(home_sit);
    }
    for (uint i = 0; i < away_active.size(); i++) {
      if (goal) away_active[i]->AddGoalAgainst(away_sit);
      if (shot) away_active[i]->AddShotAgainst(away_sit);
      away_active[i]->AddShotAttemptAgainst(away_sit);
    }
  }
  else {
    for (uint i = 0; i < away_active.size(); i++) {
      if (goal) away_active[i]->AddGoalFor(away_sit);
      if (shot) away_active[i]->AddShotFor(away_sit);
      away_active[i]->AddShotAttemptFor(away_sit);
    }
    for (uint i = 0; i < home_active.size(); i++) {
      if (goal) home_active[i]->AddGoalAgainst(home_sit);
      if (shot) home_active[i]->AddShotAgainst(home_sit);
      home_active[i]->AddShotAttemptAgainst(home_sit);
    }
  }
}

void Game::AddGoal(std::string team) {
  if (IsHome(team)) {
    home_goals++;
    AddStat(true, true, true);
  }
  else {
    away_goals++;
    AddStat(false, true, true);
  }
  if (overtime) {
    simulated = true;
  }
}

std::vector<Player*> Game::HomeActive() {
  std::vector<Player*> res = { home_LW, home_C, home_LD, home_RD };
  if (home_sit != Situation::SH) {
    res.push_back(home_RW);
  }
  return res;
}

std::vector<Player*> Game::AwayActive() {
  std::vector<Player*> res = { away_LW, away_C, away_LD, away_RD };
  if (away_sit != Situation::SH) {
    res.push_back(away_RW);
  }
  return res;
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
  if (time > 0) {
    double diff = time - this->time;
    home_shift_remaining -= diff;
    away_shift_remaining -= diff;
    for (uint i = 0; i < active_penalties.size(); i++) {
      active_penalties[i]->RemoveTime(diff);
    }
    std::vector<Player*> hp = HomeActive();
    std::vector<Player*> ap = AwayActive();
    for (uint i = 0; i < hp.size(); i++) {
      hp[i]->AddTimeOnIce(home_sit, diff);
    }
    for (uint i = 0; i < ap.size(); i++) {
      ap[i]->AddTimeOnIce(away_sit, diff);
    }
  }
  if (time < 0) {
    std::cout << time << std::endl;
  }
  this->time = time;
}

void Game::NextPeriod() {
  if (period == 3) {
    if (home_goals == away_goals) {
      period++;
      overtime = true;
    }
    else {
      simulated = true;
    }
    simulated = true;
  }
  else if (period == 4) {
    shootout = true;
    if (TrueWithProbability(0.5)) {
      home_goals++;
    }
    else {
      away_goals++;
    }
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

template <class T>
double Game::DrawFromExps(std::vector< std::pair<double, T> > &lambdas, uint &min_ind) {
  double min_time = 999999;
  min_ind = 0;
  for (uint i = 0; i < lambdas.size(); i++) {
    double time = DrawFromExp(lambdas[i].first);
    if (time < min_time) {
      min_time = time;
      min_ind = i;
    }
  }
  return min_time;
}

Player *Game::ChooseFirstAssist(Player *scorer, bool home) {
  std::vector<Player*> candidates;
  Situation sit = away_sit;
  if (home) {
    sit = home_sit;
    candidates.push_back(home_LW);
    candidates.push_back(home_C);
    if (home_sit != Situation::SH) {
      candidates.push_back(home_RW);
    }
    candidates.push_back(home_LD);
    candidates.push_back(home_RD);
  }
  else {
    candidates.push_back(away_LW);
    candidates.push_back(away_C);
    if (away_sit != Situation::SH) {
      candidates.push_back(away_RW);
    }
    candidates.push_back(away_LD);
    candidates.push_back(away_RD);
  }
  candidates.erase(std::remove(candidates.begin(), candidates.end(), scorer), candidates.end());

  std::vector<double> probs;
  for (uint i = 0; i < candidates.size(); i++) {
    probs.push_back(candidates[i]->FirstAssistsPerOnIceGoal(sit));
  }
  
  std::discrete_distribution<int> dist(probs.begin(), probs.end());
  return candidates[dist(RNG)];
}

Player *Game::ChooseSecondAssist(Player *scorer, Player *assist1, bool home) {
  std::vector<Player*> candidates;
  Situation sit = away_sit;
  if (home) {
    sit = home_sit;
    candidates.push_back(home_LW);
    candidates.push_back(home_C);
    if (home_sit != Situation::SH) {
      candidates.push_back(home_RW);
    }
    candidates.push_back(home_LD);
    candidates.push_back(home_RD);
  }
  else {
    candidates.push_back(away_LW);
    candidates.push_back(away_C);
    if (away_sit != Situation::SH) {
      candidates.push_back(away_RW);
    }
    candidates.push_back(away_LD);
    candidates.push_back(away_RD);
  }
  candidates.erase(std::remove(candidates.begin(), candidates.end(), scorer), candidates.end());
  candidates.erase(std::remove(candidates.begin(), candidates.end(), assist1), candidates.end());

  std::vector<double> probs;
  for (uint i = 0; i < candidates.size(); i++) {
    probs.push_back(candidates[i]->SecondAssistsPerOnIceGoal(sit));
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

// when penalty ends
void Game::SetEvenStrength() {
  while (active_penalties.size() > 0) {
    active_penalties.pop_back();
  }
  home_sit = Situation::EV;
  away_sit = Situation::EV;
  home_shift_remaining = SHIFT_LENGTH;
  away_shift_remaining = SHIFT_LENGTH;
  int hfwd = SelectFwdLine(true);
  int hdef = SelectDefLine(true);
  int afwd = SelectFwdLine(false);
  int adef = SelectDefLine(false);
  home_LW = home_team.LW[hfwd];
  home_C = home_team.C[hfwd];
  home_RW = home_team.RW[hfwd];
  home_LD = home_team.LD[hdef];
  home_RD = home_team.RD[hdef];
  away_LW = away_team.LW[afwd];
  away_C = away_team.C[afwd];
  away_RW = away_team.RW[afwd];
  away_LD = away_team.LD[adef];
  away_RD = away_team.RD[adef];
}

// when penalty begins
void Game::SetPowerPlay(bool home) {
  home_shift_remaining = PP_SHIFT_LENGTH;
  away_shift_remaining = PP_SHIFT_LENGTH;
  if (home) {
    home_sit = Situation::PP;
    away_sit = Situation::SH;
    home_LW = home_team.PPLW[0];
    home_C = home_team.PPC[0];
    home_RW = home_team.PPRW[0];
    home_LD = home_team.PPLD[0];
    home_RD = home_team.PPRD[0];
    away_LW = away_team.SHF1[0];
    away_C = away_team.SHF2[0];
    away_RW = NULL;
    away_LD = away_team.SHLD[0];
    away_RD = away_team.SHRD[0];
  }
  else {
    away_sit = Situation::PP;
    home_sit = Situation::SH;
    away_LW = away_team.PPLW[0];
    away_C = away_team.PPC[0];
    away_RW = away_team.PPRW[0];
    away_LD = away_team.PPLD[0];
    away_RD = away_team.PPRD[0];
    home_LW = home_team.SHF1[0];
    home_C = home_team.SHF2[0];
    home_RW = NULL;
    home_LD = home_team.SHLD[0];
    home_RD = home_team.SHRD[0];
  }
}

bool Game::EvenStrength() {
  return home_sit == Situation::EV;
}

void Game::AddPenalty(Penalty *pen) {
  active_penalties.push_back(pen);
}

void Game::RemovePenalty(Penalty *pen) {
  active_penalties.erase(std::remove(active_penalties.begin(), active_penalties.end(), pen), active_penalties.end());
}

double Game::PenaltyRemaining() {
  if (active_penalties.size() == 0) {
    return 0;
  }
  return active_penalties[0]->Remaining();
}

void Game::DrawNextEvent() {
  // draw from distribution for each active player's shot attempt rate
  std::vector< std::pair<double, Player*> > lambdas;
  lambdas.push_back(std::make_pair(home_LW->ShotAttemptsPerMinute(home_sit), home_LW));
  lambdas.push_back(std::make_pair(home_C->ShotAttemptsPerMinute(home_sit), home_C));
  if (home_sit != Situation::SH) {
    lambdas.push_back(std::make_pair(home_RW->ShotAttemptsPerMinute(home_sit), home_RW));
  }
  lambdas.push_back(std::make_pair(home_LD->ShotAttemptsPerMinute(home_sit), home_LD));
  lambdas.push_back(std::make_pair(home_RD->ShotAttemptsPerMinute(home_sit), home_RD));
  lambdas.push_back(std::make_pair(away_LW->ShotAttemptsPerMinute(away_sit), away_LW));
  lambdas.push_back(std::make_pair(away_C->ShotAttemptsPerMinute(away_sit), away_C));
  if (away_sit !=  Situation::SH) {
    lambdas.push_back(std::make_pair(away_RW->ShotAttemptsPerMinute(away_sit), away_RW));
  }
  lambdas.push_back(std::make_pair(away_LD->ShotAttemptsPerMinute(away_sit), away_LD));
  lambdas.push_back(std::make_pair(away_RD->ShotAttemptsPerMinute(away_sit), away_RD));
  
  uint min_ind;
  double attempt_time = DrawFromExps(lambdas, min_ind);

  uint pen_ind = 0;
  double penalty_time = 9999999;
  bool penalized_home = false;
  Player *penalized = NULL;
  if (home_sit == Situation::EV) {
    std::vector< std::pair<double, Player*> > plambdas;
    plambdas.push_back(std::make_pair(home_LW->PenaltiesPerMinute(home_sit), home_LW));
    plambdas.push_back(std::make_pair(home_C->PenaltiesPerMinute(home_sit), home_C));
    plambdas.push_back(std::make_pair(home_RW->PenaltiesPerMinute(home_sit), home_RW));
    plambdas.push_back(std::make_pair(home_LD->PenaltiesPerMinute(home_sit), home_LD));
    plambdas.push_back(std::make_pair(home_RD->PenaltiesPerMinute(home_sit), home_RD));
    plambdas.push_back(std::make_pair(away_LW->PenaltiesPerMinute(away_sit), away_LW));
    plambdas.push_back(std::make_pair(away_C->PenaltiesPerMinute(away_sit), away_C));
    plambdas.push_back(std::make_pair(away_RW->PenaltiesPerMinute(away_sit), away_RW));
    plambdas.push_back(std::make_pair(away_LD->PenaltiesPerMinute(away_sit), away_LD));
    plambdas.push_back(std::make_pair(away_RD->PenaltiesPerMinute(away_sit), away_RD));

    penalty_time = DrawFromExps(plambdas, pen_ind);
    penalized = plambdas[pen_ind].second;
    penalized_home = pen_ind <= 4;
  }
  
  Player *shooter = NULL;
  bool shooter_home = min_ind <= (home_sit == Situation::SH ? 3 : 4);

  std::string team = away_team.Name();
  if (shooter_home) {
    team = home_team.Name();
  }

  std::string penalized_team = away_team.Name();
  if (penalized_home) {
    penalized_team = home_team.Name();
  }

  shooter = lambdas[min_ind].second;

  Player *goalie = home_G;
  Situation shooter_sit = away_sit;
  Situation goalie_sit = home_sit;
  if (shooter_home) {
    goalie = away_G;
    shooter_sit = home_sit;
    goalie_sit = away_sit;
  }

  double period_remaining = (overtime ? 5 : 20) - time;

  Event *ev = NULL;

  // need to make a line change
  if (away_shift_remaining <= 0) {
    if (away_sit == Situation::EV) {
      int fwd_line = SelectFwdLine(false);
      int def_line = SelectDefLine(false);
      ev = new LineChange(*this, period, time, away_team.Name(),
        away_team.LW[fwd_line], away_team.C[fwd_line], away_team.RW[fwd_line],
        away_team.LD[def_line], away_team.RD[def_line]);
    }
    else if (away_sit == Situation::PP) {
      ev = new LineChange(*this, period, time, away_team.Name(),
        away_team.PPLW[1], away_team.PPC[1], away_team.PPRW[1],
        away_team.PPLD[1], away_team.PPRD[1]);
    }
    else {
      ev = new LineChange(*this, period, time, away_team.Name(),
        away_team.SHF1[1], away_team.SHF2[1], NULL,
        away_team.SHLD[1], away_team.SHRD[1]);
    }
  }
  else if (home_shift_remaining <= 0) {
    if (home_sit == Situation::EV) {
      int fwd_line = SelectFwdLine(true);
      int def_line = SelectDefLine(true);
      ev = new LineChange(*this, period, time, home_team.Name(),
        home_team.LW[fwd_line], home_team.C[fwd_line], home_team.RW[fwd_line],
        home_team.LD[def_line], home_team.RD[def_line]);
    }
    else if (home_sit == Situation::PP) {
      ev = new LineChange(*this, period, time, home_team.Name(),
        home_team.PPLW[1], home_team.PPC[1], home_team.PPRW[1],
        home_team.PPLD[1], home_team.PPRD[1]);
    }
    else {
      ev = new LineChange(*this, period, time, home_team.Name(),
        home_team.SHF1[1], home_team.SHF2[1], NULL,
        home_team.SHLD[1], home_team.SHRD[1]);
    }
  }
  // shot attempt will happen
  else if (attempt_time < penalty_time && attempt_time < period_remaining && (EvenStrength() || attempt_time < PenaltyRemaining())) {
    // if shot goes on net
    if (TrueWithProbability(shooter->ShotsPerShotAttempt(shooter_sit))) {
      double goal_prob = shooter->GoalsPerShot(shooter_sit)/(1-goalie->GoalsPerShotAgainst(goalie_sit)+shooter->GoalsPerShot(shooter_sit));
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

        ev = new Goal(*this, period, time + attempt_time, team, shooter, assist1, assist2, shooter_sit);
      }
      else {
        ev = new Shot(*this, period, time + attempt_time, team, shooter, goalie, shooter_sit);
      }
    }
    else {
      ev = new ShotAttempt(*this, period, time + attempt_time, team, shooter, shooter_sit);
    }
  }
  // penalty occurs
  else if (EvenStrength() && penalty_time < period_remaining) {
    ev = new Penalty(*this, period, time + penalty_time, penalized_team, penalized);
  }
  // penalty ends
  else if (!EvenStrength() && attempt_time >= PenaltyRemaining() && PenaltyRemaining() < period_remaining) {
    ev = new PenaltyEnd(*this, period, time + PenaltyRemaining(), active_penalties[0]);
  }
  // period ends
  else {
    ev = new PeriodEnd(*this, period);
  }

  game_log.push_back(ev);
}

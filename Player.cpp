#include <iostream>
#include "Player.hpp"
#include "Probability.hpp"

std::string &Player::Name() {
  return name;
}

std::vector<Position> &Player::Positions() {
  return bio.Positions();
}

void Player::setBio(BioStats &bio) {
  this->bio = bio;
}

void Player::addIndividualStats(Situation sit, IndividualStats &ind) {
  if (sit == Situation::EV) {
    individual.push_back(ind);
    total_individual.AddStats(ind);
  }
  else if (sit == Situation::PP) {
    pp_individual.push_back(ind);
    total_pp_individual.AddStats(ind);
  }
  else {
    sh_individual.push_back(ind);
    total_sh_individual.AddStats(ind);
  }
}

void Player::addOnIceStats(Situation sit, OnIceStats &on_ice) {
  if (sit == Situation::EV) {
    this->on_ice.push_back(on_ice);
    total_on_ice.AddStats(on_ice);
  }
  else if (sit == Situation::PP) {
    pp_on_ice.push_back(on_ice);
    total_pp_on_ice.AddStats(on_ice);
  }
  else {
    sh_on_ice.push_back(on_ice);
    total_sh_on_ice.AddStats(on_ice);
  }
}

IndividualStats &Player::LastSeasonIndividual(Situation sit) {
  if (sit == Situation::EV) {
    return individual[0];
  }
  if (sit == Situation::PP) {
    return pp_individual[0];
  }
  return sh_individual[0];
}

OnIceStats &Player::LastSeasonOnIce(Situation sit) {
  if (sit == Situation::EV) {
    return on_ice[0];
  }
  if (sit == Situation::PP) {
    return pp_on_ice[0];
  }
  return sh_on_ice[0];
}

Player::Prediction &Player::SituationPrediction(Situation sit) {
  switch (sit) {
  case Situation::EV:
    return pred;
  case Situation::PP:
    return pp_pred;
  case Situation::SH:
    return sh_pred;
  }
  return pred;
}

double Player::OnIceShotAttemptsPerMinute(Situation sit) {
  return SituationPrediction(sit).on_ice_shot_attempts_per_minute;
}

double Player::ShotAttemptsPerMinute(Situation sit) {
  return SituationPrediction(sit).shot_attempts_per_minute;
}

double Player::ShotsPerShotAttempt(Situation sit) {
  return SituationPrediction(sit).shots_per_shot_attempt;
}

double Player::GoalsPerShot(Situation sit) {
  return SituationPrediction(sit).goals_per_shot;
}

double Player::FirstAssistsPerOnIceShot(Situation sit) {
  return SituationPrediction(sit).first_assists_per_on_ice_shot;
}

double Player::FirstAssistsPerOnIceGoal(Situation sit) {
  return SituationPrediction(sit).first_assists_per_on_ice_goal;
}

double Player::SecondAssistsPerOnIceGoal(Situation sit) {
  return SituationPrediction(sit).second_assists_per_on_ice_goal;
}

double Player::PenaltiesPerMinute(Situation sit) {
  return SituationPrediction(sit).penalties_per_minute;
}

double Player::PKMinutesPerGame() {
  return total_sh_individual.TimeOnIce() / total_individual.GamesPlayed();
}

int Player::GamesPlayed() {
  return current_individual[Situation::EV].GamesPlayed();
}

int Player::Points() {
  int points = 0;
  for (int i = 0; i < 3; i++) {
    points += current_individual[i].Points();
  }
  return points;
}

int Player::Fatigue() {
  return fatigue;
}

void Player::PrintIndividualStats() {
  IndividualStats total;
  for (uint i = 0; i < 3; i++) {
    total.AddStats(current_individual[i]);
  }
  total.Print(name);
}

void Player::ResetStats() {
  IndividualStats total;
  for (uint i = 0; i < 3; i++) {
    total.AddStats(current_individual[i]);
    current_individual[i] = IndividualStats();
  }
  gen_individual.push_back(total);

}

double Player::GoalsPerShotAgainst(Situation sit) {
  return SituationPrediction(sit).goals_per_shot_against;
}

bool Player::IsForward() {
  Position fp = Positions()[0];
  return fp == Position::LW || fp == Position::C || fp == Position::RW;
}

bool Player::IsDefense() {
  Position fp = Positions()[0];
  return fp == Position::LD || fp == Position::RD || fp == Position::D;
}

bool Player::IsGoalie() {
  return Positions()[0] == Position::G;
}

bool Player::Ready() {
  if (!predicted) {
    std::cerr << "Player " << name << " not ready!" << std::endl;
  }
  return predicted;
}

void Player::Predict(Replacement &repl) {
  // Fill in the predictions.

  IndividualStats &ind = total_individual;
  IndividualStats &pp_ind = total_pp_individual;
  IndividualStats &sh_ind = total_sh_individual;
  OnIceStats &onice = total_on_ice;
  OnIceStats &pp_onice = total_pp_on_ice;
  OnIceStats &sh_onice = total_sh_on_ice;

  // EVEN STRENGTH PREDICTIONS
  // If insufficient data is found, add in replacement level stats
  if (ind.TimeOnIce() < 300) {
    ind.AddStats(repl.Individual(Situation::EV, Positions()[0]));
    onice.AddStats(repl.OnIce(Situation::EV, Positions()[0]));
  }
  pred.on_ice_shot_attempts_per_minute = ((double)onice.Shots()) / ind.TimeOnIce();
  pred.shot_attempts_per_minute = ((double)ind.ShotAttempts()) / ind.TimeOnIce();
  pred.shots_per_shot_attempt = ((double)ind.Shots()) / ind.ShotAttempts();
  pred.goals_per_shot = ((double)ind.Goals()) / ind.Shots();
  pred.first_assists_per_on_ice_shot = ((double)ind.FirstAssists()) / onice.Shots();
  pred.first_assists_per_on_ice_goal = ((double)ind.FirstAssists()) / onice.Goals();
  pred.second_assists_per_on_ice_goal = ((double)ind.SecondAssists()) / onice.Goals();
  pred.penalties_per_minute = ((double)ind.Penalties()) / ind.TimeOnIce();
  pred.goals_per_shot_against = ((double)onice.GoalsAgainst())/onice.ShotsAgainst();

  if (pp_ind.TimeOnIce() < 100) {
    pp_ind.AddStats(repl.Individual(Situation::PP, Positions()[0]));
    pp_onice.AddStats(repl.OnIce(Situation::PP, Positions()[0]));
  }
  pp_pred.shot_attempts_per_minute = ((double)pp_ind.ShotAttempts())/pp_ind.TimeOnIce();
  pp_pred.shots_per_shot_attempt = ((double)pp_ind.Shots())/pp_ind.ShotAttempts();
  pp_pred.goals_per_shot = ((double)pp_ind.Goals()) / pp_ind.Shots();
  pp_pred.first_assists_per_on_ice_shot = ((double)pp_ind.FirstAssists())/pp_onice.Shots();
  pp_pred.first_assists_per_on_ice_goal = ((double)pp_ind.FirstAssists())/pp_onice.Goals();
  pp_pred.second_assists_per_on_ice_goal = ((double)pp_ind.SecondAssists())/pp_onice.Goals();
  pp_pred.goals_per_shot_against = ((double)pp_onice.GoalsAgainst())/pp_onice.ShotsAgainst();

  if (sh_ind.TimeOnIce() < 100) {
    sh_ind.AddStats(repl.Individual(Situation::SH, Positions()[0]));
    sh_onice.AddStats(repl.OnIce(Situation::SH, Positions()[0]));
  }
  sh_pred.shot_attempts_per_minute = ((double)sh_ind.ShotAttempts())/sh_ind.TimeOnIce();
  sh_pred.shots_per_shot_attempt = ((double)sh_ind.Shots())/sh_ind.ShotAttempts();
  sh_pred.goals_per_shot = ((double)sh_ind.Goals()) / sh_ind.Shots();
  sh_pred.first_assists_per_on_ice_shot = ((double)sh_ind.FirstAssists())/sh_onice.Shots();
  sh_pred.first_assists_per_on_ice_goal = ((double)sh_ind.FirstAssists())/sh_onice.Goals();
  sh_pred.second_assists_per_on_ice_goal = ((double)sh_ind.SecondAssists())/sh_onice.Goals();
  sh_pred.goals_per_shot_against = ((double)sh_onice.GoalsAgainst())/sh_onice.ShotsAgainst();

  GenerateShotAttempt(Situation::EV);
  GenerateShotAttempt(Situation::PP);
  GenerateShotAttempt(Situation::SH);
  GeneratePenalty();
  
  predicted = true;
}

void Player::AddGamePlayed() {
  fatigue += 2;
  current_individual[Situation::EV].AddGamePlayed();
}

void Player::AddTimeOnIce(Situation sit, double time) {
  current_individual[sit].AddTimeOnIce(time);
  shot_attempt_time[sit] -= time;
  if (shot_attempt_time[sit] < 0) {
    shot_attempt_time[sit] = 0;
  }
  penalty_time -= time;
  if (penalty_time < 0) {
    penalty_time = 0;
  }
}

void Player::AddShotAttempt(Situation sit) {
  current_individual[sit].AddShotAttempt();
  GenerateShotAttempt(sit);
}

void Player::AddShotAttemptFor(Situation sit) {
  current_on_ice[sit].AddShotAttempt();
}

void Player::AddShotAttemptAgainst(Situation sit) {
  current_on_ice[sit].AddShotAttemptAgainst();
}

void Player::AddShot(Situation sit) {
  current_individual[sit].AddShot();
}

void Player::AddShotFor(Situation sit) {
  current_on_ice[sit].AddShot();
}

void Player::AddShotAgainst(Situation sit) {
  current_on_ice[sit].AddShotAgainst();
}

void Player::AddGoal(Situation sit) {
  current_individual[sit].AddGoal();
}

void Player::AddGoalFor(Situation sit) {
  current_on_ice[sit].AddGoal();
}

void Player::AddGoalAgainst(Situation sit) {
  current_on_ice[sit].AddGoalAgainst();
}

void Player::AddFirstAssist(Situation sit) {
  current_individual[sit].AddFirstAssist();
}

void Player::AddSecondAssist(Situation sit) {
  current_individual[sit].AddSecondAssist();
}

void Player::AddPenalty() {
  current_individual[Situation::EV].AddPenalty();
  GeneratePenalty();
}

void Player::PassDay() {
  fatigue -= 1;
  if (fatigue < 0) {
    fatigue = 0;
  }
}

void Player::GenerateShotAttempt(Situation sit) {
  shot_attempt_time[sit] = Probability::DrawFromExp(ShotAttemptsPerMinute(sit));
}

void Player::GeneratePenalty() {
  penalty_time = Probability::DrawFromExp(PenaltiesPerMinute(Situation::EV));
}

double Player::ShotAttemptTime(Situation sit) {
  return shot_attempt_time[sit];
}

double Player::PenaltyTime() {
  return penalty_time;
}

#include "Player.hpp"
#include <iostream>

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

double Player::PenaltiesPerMinute(Situation sit) {
  return SituationPrediction(sit).penalties_per_minute;
}

double Player::GoalsPerShotAgainst(Situation sit) {
  return SituationPrediction(sit).goals_per_shot_against;
}

bool Player::IsDefense() {
  Position fp = Positions()[0];
  return fp == Position::LD || Position::RD || Position::D;
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

  // TODO replace these with actual predictions. For now I'm just copying
  //  their previous season's results.

  IndividualStats &ind = total_individual;
  IndividualStats &pp_ind = total_pp_individual;
  IndividualStats &sh_ind = total_sh_individual;
  OnIceStats &onice = total_on_ice;
  OnIceStats &pp_onice = total_pp_on_ice;
  OnIceStats &sh_onice = total_sh_on_ice;

  // EVEN STRENGTH PREDICTIONS
  // If insufficient data is found, assume replacement level
  if (individual.size() == 0 || individual[0].TimeOnIce() < 200) {
    ind = repl.Individual(Situation::EV, Positions()[0]);
    onice = repl.OnIce(Situation::EV, Positions()[0]);
  }
  pred.on_ice_shot_attempts_per_minute = ((double)onice.Shots()) / ind.TimeOnIce();
  pred.shot_attempts_per_minute = ((double)ind.ShotAttempts()) / ind.TimeOnIce();
  pred.shots_per_shot_attempt = ((double)ind.Shots()) / ind.ShotAttempts();
  pred.goals_per_shot = ((double)ind.Goals()) / ind.Shots();
  pred.first_assists_per_on_ice_shot = ((double)ind.FirstAssists()) / onice.Shots();
  pred.penalties_per_minute = ((double)ind.Penalties()) / ind.TimeOnIce();
  pred.goals_per_shot_against = ((double)onice.GoalsAgainst())/onice.ShotsAgainst();

  if (pp_individual.size() == 0 || pp_individual[0].TimeOnIce() < 100) {
    pp_ind = repl.Individual(Situation::PP, Positions()[0]);
    pp_onice = repl.OnIce(Situation::PP, Positions()[0]);
  }
  pp_pred.shot_attempts_per_minute = ((double)pp_ind.ShotAttempts())/pp_ind.TimeOnIce();
  pp_pred.shots_per_shot_attempt = ((double)pp_ind.Shots())/pp_ind.ShotAttempts();
  pp_pred.goals_per_shot = ((double)pp_ind.Goals()) / pp_ind.Shots();
  pp_pred.first_assists_per_on_ice_shot = ((double)pp_ind.FirstAssists())/pp_onice.Shots();
  pp_pred.goals_per_shot_against = ((double)pp_onice.GoalsAgainst())/pp_onice.ShotsAgainst();

  if (sh_individual.size() == 0 || sh_individual[0].TimeOnIce() < 100) {
    sh_ind = repl.Individual(Situation::SH, Positions()[0]);
    sh_onice = repl.OnIce(Situation::SH, Positions()[0]);
  }
  sh_pred.shot_attempts_per_minute = ((double)sh_ind.ShotAttempts())/sh_ind.TimeOnIce();
  sh_pred.shots_per_shot_attempt = ((double)sh_ind.Shots())/sh_ind.ShotAttempts();
  sh_pred.goals_per_shot = ((double)sh_ind.Goals()) / sh_ind.Shots();
  sh_pred.first_assists_per_on_ice_shot = ((double)sh_ind.FirstAssists())/sh_onice.Shots();
  sh_pred.goals_per_shot_against = ((double)sh_onice.GoalsAgainst())/sh_onice.ShotsAgainst();

  predicted = true;
}

void Player::ScoreGoal() {
  goals++;
}

void Player::ScoreFirstAssist() {
  first_assists++;
}

void Player::ScoreSecondAssist() {
  second_assists++;
}

void Player::ScoreGoalAgainst() {
  goals_against++;
}

#include "Player.hpp"
#include <iostream>

std::string &Player::Name() {
  return name;
}

std::vector<Position> &Player::Positions() {
  return bio.Positions();
}

void Player::setBio(BioStats bio) {
  this->bio = bio;
}

void Player::addIndividualStats(IndividualStats ind) {
  individual.push_back(ind);
}

void Player::addOnIceStats(OnIceStats on_ice) {
  this->on_ice.push_back(on_ice);
}

double Player::OnIceShotAttemptsPerMinute() {
  return predicted_on_ice_shot_attempts_per_minute;
}

double Player::ShotAttemptsPerMinute() {
  return predicted_shot_attempts_per_minute;
}

double Player::ShotsPerShotAttempt() {
  return predicted_shots_per_shot_attempt;
}

double Player::GoalsPerShot() {
  return predicted_goals_per_shot;
}

double Player::FirstAssistsPerOnIceShot() {
  return predicted_first_assists_per_on_ice_shot;
}

double Player::PenaltiesPerMinute() {
  return predicted_penalties_per_minute;
}

double Player::GoalsPerShotAgainst() {
  return predicted_goals_per_shot_against;
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

void Player::Predict() {
  // Fill in the predicted fields.

  // If insufficient data is found, assume replacement level
  if (individual.size() == 0 || individual[0].TimeOnIce() < 200) {
    predicted_on_ice_shot_attempts_per_minute = 0.84;
    if (IsDefense()) {
      predicted_shot_attempts_per_minute = 0.14;
      predicted_shots_per_shot_attempt = 0.5;
      predicted_goals_per_shot = 0.025;
      predicted_first_assists_per_on_ice_shot = 0.015;
      predicted_penalties_per_minute = 0.00957;
    }
    else {
      predicted_shot_attempts_per_minute = 0.23;
      predicted_shots_per_shot_attempt = 0.55;
      predicted_goals_per_shot = 0.08;
      predicted_first_assists_per_on_ice_shot = 0.015;
      predicted_penalties_per_minute = 0.0118;
    }
    predicted_goals_per_shot_against = 0.09; // sv pctg 0.910 ???
    predicted = true;
    return;
  }

  // TODO replace these with actual predictions. For now I'm just copying
  //  their previous season's results.
  IndividualStats &ind = individual[individual.size() - 1];
  OnIceStats &onice = on_ice[on_ice.size() - 1];
  predicted_on_ice_shot_attempts_per_minute = ((double)onice.Shots()) / ind.TimeOnIce();
  predicted_shot_attempts_per_minute = ((double)ind.ShotAttempts()) / ind.TimeOnIce();
  predicted_shots_per_shot_attempt = ((double)ind.Shots()) / ind.ShotAttempts();
  predicted_goals_per_shot = ind.ShootingPercentage() / 100;
  predicted_first_assists_per_on_ice_shot = ((double)ind.FirstAssists()) / onice.Shots();
  predicted_penalties_per_minute = ((double)ind.Penalties()) / ind.TimeOnIce();
  predicted_goals_per_shot_against = ((double)onice.GoalsAgainst())/onice.ShotsAgainst();
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

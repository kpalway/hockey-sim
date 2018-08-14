#include "Stats.hpp"

#ifndef ONICESTATS_HPP
#define ONICESTATS_HPP

class OnIceStats : public Stats {
public:
  int ShotAttempts();
  int ShotAttemptsAgainst();
  double ShotAttemptShare();
  int UnblockedShotAttempts();
  int UnblockedShotAttemptsAgainst();
  double UnblockedShotAttemptShare();
  int Shots();
  int ShotsAgainst();
  double ShotShare();
  int Goals();
  int GoalsAgainst();
  double GoalShare();
  int ScoringChances();
  int ScoringChancesAgainst();
  double ScoringChanceShare();
  int HighDangerScoringChances();
  int HighDangerScoringChancesAgainst();
  double HighDangerScoringChanceShare();
  int HighDangerGoals();
  int HighDangerGoalsAgainst();
  double HighDangerGoalShare();
  double OnIceShootingPercentage();
  double OnIceSavePercentage();
  double PDO();
  int OffensiveZoneFaceoffs();
  int NeutralZoneFaceoffs();
  int DefensiveZoneFaceoffs();
  double OffensiveZoneFaceoffPercentage();

  void loadData(std::vector<std::string> &data);
private:
  int shot_attempts;
  int shot_attempts_against;
  int unblocked_shot_attempts;
  int unblocked_shot_attempts_against;
  int shots;
  int shots_against;
  int goals;
  int goals_against;
  int scoring_chances;
  int scoring_chances_against;
  int high_danger_scoring_chances;
  int high_danger_scoring_chances_against;
  int high_danger_goals;
  int high_danger_goals_against;
  int offensive_zone_faceoffs;
  int neutral_zone_faceoffs;
  int defensive_zone_faceoffs;
};

#endif // ONICESTATS_HPP

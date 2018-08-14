#include <string>
#include "Position.hpp"
#include "BioStats.hpp"
#include "IndividualStats.hpp"
#include "OnIceStats.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
public:
  Player() { }
  Player(std::string name) : name(name) { }

  std::string &Name();
  std::vector<Position> &Positions();

  void setBio(BioStats bio);
  void addIndividualStats(IndividualStats ind);
  void addOnIceStats(OnIceStats on_ice);

  double OnIceShotAttemptsPerMinute();
  double ShotAttemptsPerMinute();
  double ShotsPerShotAttempt();
  double GoalsPerShot();
  double FirstAssistsPerOnIceShot();

  double PenaltiesPerMinute();

  void Predict();

  void ScoreGoal();
  void ScoreFirstAssist();
  void ScoreSecondAssist();
  void ScoreGoalAgainst();

  bool IsDefense();
  bool IsGoalie();

private:
  std::string name;
  BioStats bio;
  std::vector<IndividualStats> individual;
  std::vector<OnIceStats> on_ice;

  double predicted_on_ice_shot_attempts_per_minute;
  double predicted_shot_attempts_per_minute;
  double predicted_shots_per_shot_attempt;
  double predicted_goals_per_shot;
  double predicted_first_assists_per_on_ice_shot;
  double predicted_penalties_per_minute;

  int goals;
  int first_assists;
  int second_assists;
  int goals_against;
};

#endif // PLAYER_HPP

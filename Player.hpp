#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Position.hpp"
#include "BioStats.hpp"
#include "IndividualStats.hpp"
#include "OnIceStats.hpp"
#include "Situation.hpp"
#include "Replacement.hpp"

class Player {
public:
  Player(std::string name) : name(name), predicted(false), fatigue(0) { }

  std::string &Name();
  std::vector<Position> &Positions();

  void setBio(BioStats &bio);
  void addIndividualStats(Situation sit, IndividualStats &ind);
  void addOnIceStats(Situation sit, OnIceStats &on_ice);
  IndividualStats &LastSeasonIndividual(Situation sit);
  OnIceStats &LastSeasonOnIce(Situation sit);

  double OnIceShotAttemptsPerMinute(Situation sit);
  double ShotAttemptsPerMinute(Situation sit);
  double ShotsPerShotAttempt(Situation sit);
  double GoalsPerShot(Situation sit);
  double FirstAssistsPerOnIceShot(Situation sit);
  double FirstAssistsPerOnIceGoal(Situation sit);
  double SecondAssistsPerOnIceGoal(Situation sit);
  double GoalsPerShotAgainst(Situation sit);
  double PenaltiesPerMinute(Situation sit);

  double PKMinutesPerGame();
  int GamesPlayed();
  int Points();
  int Fatigue();
  void PrintIndividualStats();
  void ResetStats();

  bool Ready();
  void Predict(Replacement &repl);

  void AddGamePlayed();
  void AddTimeOnIce(Situation sit, double time);
  void AddShotAttempt(Situation sit);
  void AddShotAttemptFor(Situation sit);
  void AddShotAttemptAgainst(Situation sit);
  void AddShot(Situation sit);
  void AddShotFor(Situation sit);
  void AddShotAgainst(Situation sit);
  void AddGoal(Situation sit);
  void AddGoalFor(Situation sit);
  void AddGoalAgainst(Situation sit);
  void AddFirstAssist(Situation sit);
  void AddSecondAssist(Situation sit);
  void AddPenalty();

  bool IsForward();
  bool IsDefense();
  bool IsGoalie();

  void PassDay();
  void GenerateShotAttempt(Situation sit);
  void GeneratePenalty();

  double ShotAttemptTime(Situation sit);
  double PenaltyTime();

private:
  std::string name;
  BioStats bio;
  IndividualStats total_individual;
  IndividualStats total_pp_individual;
  IndividualStats total_sh_individual;
  std::vector<IndividualStats> individual;
  std::vector<IndividualStats> pp_individual;
  std::vector<IndividualStats> sh_individual;
  OnIceStats total_on_ice;
  OnIceStats total_pp_on_ice;
  OnIceStats total_sh_on_ice;
  std::vector<OnIceStats> on_ice;
  std::vector<OnIceStats> pp_on_ice;
  std::vector<OnIceStats> sh_on_ice;

  std::vector<IndividualStats> gen_individual;

  IndividualStats current_individual[3];
  OnIceStats current_on_ice[3];

  bool predicted;
  struct Prediction {
    double on_ice_shot_attempts_per_minute;
    double shot_attempts_per_minute;
    double shots_per_shot_attempt;
    double goals_per_shot;
    double first_assists_per_on_ice_shot;
    double first_assists_per_on_ice_goal;
    double second_assists_per_on_ice_goal;
    double penalties_per_minute;

    double goals_per_shot_against;
  };

  Prediction pred;
  Prediction pp_pred;
  Prediction sh_pred;

  Prediction &SituationPrediction(Situation sit);

  int fatigue;
  double penalty_time;
  double shot_attempt_time[3];
};

#endif // PLAYER_HPP

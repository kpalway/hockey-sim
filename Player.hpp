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
  Player(std::string name) : name(name), predicted(false) { }

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
  double GoalsPerShotAgainst(Situation sit);
  double PenaltiesPerMinute(Situation sit);

  bool Ready();
  void Predict(Replacement &repl);

  void ScoreGoal();
  void ScoreFirstAssist();
  void ScoreSecondAssist();
  void ScoreGoalAgainst();

  bool IsDefense();
  bool IsGoalie();

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

  bool predicted;
  struct Prediction {
    double on_ice_shot_attempts_per_minute;
    double shot_attempts_per_minute;
    double shots_per_shot_attempt;
    double goals_per_shot;
    double first_assists_per_on_ice_shot;
    double penalties_per_minute;

    double goals_per_shot_against;
  };

  Prediction pred;
  Prediction pp_pred;
  Prediction sh_pred;

  Prediction &SituationPrediction(Situation sit);

  int goals;
  int first_assists;
  int second_assists;
  int goals_against;
};

#endif // PLAYER_HPP

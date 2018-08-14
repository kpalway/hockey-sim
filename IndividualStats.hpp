#include "Stats.hpp"

#ifndef INDIVIDUALSTATS_HPP
#define INDIVIDUALSTATS_HPP

class IndividualStats : public Stats {
public:
  int GamesPlayed();
  double TimeOnIce();
  int Goals();
  int Assists();
  int FirstAssists();
  int SecondAssists();
  int Points();
  int PrimaryPoints();
  int Shots();
  double ShootingPercentage();
  int ShotAttempts();
  int UnblockedShotAttempts();
  int ScoringChances();
  int HighDangerScoringChances();
  int RushAttempts();
  int ReboundsCreated();
  int PenaltyMinutes();
  int Penalties();
  int MinorPenalties();
  int MajorPenalties();
  int Misconducts();
  int PenaltiesDrawn();
  int Giveaways();
  int Takeaways();
  int Hits();
  int HitsTaken();
  int ShotsBlocked();
  int FaceoffsWon();
  int FaceoffsLost();
  double FaceoffPercentage();

  void loadData(std::vector<std::string> &data);
private:
  int games_played;
  double time_on_ice;
  int goals;
  int first_assists;
  int second_assists;
  int shots;
  double shooting_percentage;
  int shot_attempts;
  int unblocked_shot_attempts;
  int scoring_chances;
  int high_danger_scoring_chances;
  int rush_attempts;
  int rebounds_created;
  int penalty_minutes;
  int minor_penalties;
  int major_penalties;
  int misconducts;
  int penalties_drawn;
  int giveaways;
  int takeaways;
  int hits;
  int hits_taken;
  int shots_blocked;
  int faceoffs_won;
  int faceoffs_lost;
};

#endif // INDIVIDUALSTATS_HPP

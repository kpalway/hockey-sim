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
  void AddStats(IndividualStats &other);

  void AddGamePlayed();
  void AddTimeOnIce(double time);
  void AddShotAttempt();
  void AddShot();
  void AddGoal();
  void AddFirstAssist();
  void AddSecondAssist();
  void AddPenalty();

  static void PrintHeading();
  void Print(std::string player);

  IndividualStats(): games_played(0), time_on_ice(0), goals(0), first_assists(0),
    second_assists(0), shots(0), shot_attempts(0), unblocked_shot_attempts(0),
    scoring_chances(0), high_danger_scoring_chances(0), rush_attempts(0),
    rebounds_created(0), penalty_minutes(0), minor_penalties(0), major_penalties(0),
    misconducts(0), penalties_drawn(0), giveaways(0), takeaways(0), hits(0),
    hits_taken(0), shots_blocked(0), faceoffs_won(0), faceoffs_lost(0) { }
private:
  int games_played;
  double time_on_ice;
  int goals;
  int first_assists;
  int second_assists;
  int shots;
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

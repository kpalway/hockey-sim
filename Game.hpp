#ifndef GAME_HPP
#define GAME_HPP

class Game;
class Event;
class Penalty;

#include <utility>
#include <vector>
#include <string>
#include "Team.hpp"
#include "Penalty.hpp"
#include "Player.hpp"
#include "Situation.hpp"

#define SHIFT_LENGTH 0.75
#define PP_SHIFT_LENGTH 1.1

class Game {
public:
  Game(Team &home, Team &away) : home_team(home), away_team(away), simulated(false), overtime(false), shootout(false) { }
  ~Game();
  bool Ready();
  void Simulate();
  void PrintBoxScore();
  bool HomeWins();
  bool Tied();

  void AddShotAttempt(std::string team);
  void AddShot(std::string team);
  void AddGoal(std::string team);
  void SetActiveLine(std::string team, Player *LW, Player *C, Player *RW, Player *LD, Player *RD);
  void SetTime(double time);
  void NextPeriod();
  bool IsHome(std::string &team);
  void AddPenalty(Penalty *pen);
  void RemovePenalty(Penalty *pen);
  double PenaltyRemaining();
  bool EvenStrength();
  void SetEvenStrength();
  void SetPowerPlay(bool home);
private:
  Team &home_team;
  Team &away_team;

  bool simulated;
  bool overtime;
  bool shootout;
  int period;
  double time;
  double home_shift_remaining;
  double away_shift_remaining;
  int home_goals;
  int away_goals;
  std::vector<Penalty*> active_penalties;
  Situation home_sit, away_sit;

  Player *home_LW;
  Player *home_C;
  Player *home_RW;
  Player *home_LD;
  Player *home_RD;
  Player *home_G;

  Player *away_LW;
  Player *away_C;
  Player *away_RW;
  Player *away_LD;
  Player *away_RD;
  Player *away_G;

  std::vector<Player*> HomeActive();
  std::vector<Player*> AwayActive();
  std::vector<Player*> AllActive();
  void AddStat(bool home, bool goal, bool shot);

  void GenerateShotAttempts();
  void GeneratePenalties();
  Player *ChooseFirstAssist(Player *scorer, bool home);
  Player *ChooseSecondAssist(Player *scorer, Player *assist1, bool home);
  int SelectFwdLine(bool home);
  int SelectDefLine(bool home);
  void DrawNextEvent();
  bool PlayerIsHome(Player *p);
  double NextShotAttempt(Player* &p);
  double NextPenalty(Player* &p);

  std::vector<Event*> game_log;
};

#endif // GAME_HPP

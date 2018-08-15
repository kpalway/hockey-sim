#ifndef GAME_HPP
#define GAME_HPP

class Game;
class Event;
class Penalty;

#include <vector>
#include <string>
#include <random>
#include "Team.hpp"
#include "Penalty.hpp"
#include "Player.hpp"

#define SHIFT_LENGTH 0.75

class Game {
public:
  Game(std::default_random_engine &RNG, Team &home, Team &away) : home_team(home), away_team(away), simulated(false), RNG(RNG) { }
  ~Game();
  bool Ready();
  void Simulate();
  void PrintBoxScore();
  bool HomeWins();
  bool Tied();

  void AddGoal(std::string team);
  void SetActiveLine(std::string team, Player *LW, Player *C, Player *RW, Player *LD, Player *RD);
  void SetTime(double time);
  void NextPeriod();
  bool IsHome(std::string &team);
private:
  Team &home_team;
  Team &away_team;

  bool simulated;
  int period;
  double time;
  double home_shift_remaining;
  double away_shift_remaining;
  int home_goals;
  int away_goals;
  std::vector<Penalty> active_penalties;

  std::default_random_engine &RNG;

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

  double DrawFromExp(double lambda);
  double DrawFromExps(std::vector<double> &lambdas, uint &min_ind);
  bool TrueWithProbability(double prob);
  Player *ChooseFirstAssist(Player *scorer, bool home);
  Player *ChooseSecondAssist(Player *scorer, Player *assist1, bool home);
  int SelectFwdLine(bool home);
  int SelectDefLine(bool home);
  void DrawNextEvent();

  std::vector<Event*> game_log;
};

#endif // GAME_HPP

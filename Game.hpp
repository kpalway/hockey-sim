#ifndef GAME_HPP
#define GAME_HPP

class Game;
class Event;
class Penalty;

#include <vector>
#include <string>
#include "Team.hpp"
#include "Penalty.hpp"
#include "Player.hpp"

class Game {
public:
  Game(Team &home, Team &away) : home_team(home), away_team(away), simulated(false) { }
  ~Game();
  void Simulate();

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
  int home_goals;
  int away_goals;
  std::vector<Penalty> active_penalties;

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

  void DrawNextEvent();

  std::vector<Event*> game_log;
};

#endif // GAME_HPP

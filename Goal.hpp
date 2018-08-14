#ifndef GOAL_HPP
#define GOAL_HPP

#include "Event.hpp"

class Player;

class Goal : public Event {
public:
  Goal(Game &game, int period, double time, std::string team, Player *scorer, Player *assist1, Player *assist2):
    Event(EventType::GOAL, game, period, time), team(team), scorer(scorer), assist1(assist1), assist2(assist2) { }
  void print();
  void apply();
private:
  std::string team;
  Player *scorer;
  Player *assist1;
  Player *assist2;
};

#endif // GOAL_HPP

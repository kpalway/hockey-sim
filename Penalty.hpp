#ifndef PENALTY_HPP
#define PENALTY_HPP

#include "Event.hpp"

class Player;

class Penalty : public Event {
public:
  Penalty(Game &game, int period, double time, std::string team, Player *offender):
    Event(EventType::PENALTY, game, period, time), team(team), offender(offender), remaining(2) { }
  void print();
  void apply();
  double Remaining();
  void RemoveTime(double time);
private:
  std::string team;
  Player *offender;
  double remaining;
};

#endif // PENALTY_HPP

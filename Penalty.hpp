#ifndef PENALTY_HPP
#define PENALTY_HPP

#include "Event.hpp"

class Player;

class Penalty : public Event {
public:
  Penalty(Game &game, int period, double time, Player *offender):
    Event(EventType::PENALTY, game, period, time), offender(offender) { }
  void print();
  void apply();
private:
  Player *offender;
};

#endif // PENALTY_HPP

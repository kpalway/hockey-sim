#ifndef SHOTATTEMPT_HPP
#define SHOTATTEMPT_HPP

#include "Event.hpp"

class Player;

class ShotAttempt : public Event {
public:
  ShotAttempt(Game &game, int period, double time, Player *p):
    Event(EventType::SHOT_ATTEMPT, game, period, time), player(p) { }
  void print();
  void apply();
private:
  Player *player;
};

#endif // SHOTATTEMPT_HPP

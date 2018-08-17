#ifndef SHOTATTEMPT_HPP
#define SHOTATTEMPT_HPP

#include <string>
#include "Event.hpp"

class Player;

class ShotAttempt : public Event {
public:
  ShotAttempt(Game &game, int period, double time, std::string team, Player *p):
    Event(EventType::SHOT_ATTEMPT, game, period, time), team(team), player(p) { }
  void print();
  void apply();
private:
  std::string team;
  Player *player;
};

#endif // SHOTATTEMPT_HPP

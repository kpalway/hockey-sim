#ifndef SHOT_HPP
#define SHOT_HPP

#include "Event.hpp"

class Player;

class Shot : public Event {
public:
  Shot(Game &game, int period, double time, Player *shooter, Player *goalie):
    Event(EventType::SHOT, game, period, time), shooter(shooter), goalie(goalie) { }
  void print();
  void apply();
private:
  Player *shooter;
  Player *goalie;
};

#endif // SHOT_HPP

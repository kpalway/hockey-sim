#ifndef SHOTATTEMPT_HPP
#define SHOTATTEMPT_HPP

#include <string>
#include "Event.hpp"
#include "Situation.hpp"

class Player;

class ShotAttempt : public Event {
public:
  ShotAttempt(Game &game, int period, double time, std::string team, Player *p, Situation sit):
    Event(EventType::SHOT_ATTEMPT, game, period, time), team(team), player(p), sit(sit) { }
  void print();
  void apply();
private:
  std::string team;
  Player *player;
  Situation sit;
};

#endif // SHOTATTEMPT_HPP

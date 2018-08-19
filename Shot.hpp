#ifndef SHOT_HPP
#define SHOT_HPP

#include <string>
#include "Event.hpp"
#include "Situation.hpp"

class Player;

class Shot : public Event {
public:
  Shot(Game &game, int period, double time, std::string team, Player *shooter, Player *goalie, Situation sit):
    Event(EventType::SHOT, game, period, time), team(team), shooter(shooter), goalie(goalie), sit(sit) { }
  void print();
  void apply();
private:
  std::string team;
  Player *shooter;
  Player *goalie;
  Situation sit;
};

#endif // SHOT_HPP

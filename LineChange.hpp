#ifndef LINECHANGE_HPP
#define LINECHANGE_HPP

#include "Event.hpp"

class Player;

class LineChange : public Event {
public:
  LineChange(Game &game, int period, double time, std::string team, Player *LW, Player *C, Player *RW, Player *LD, Player *RD):
    Event(EventType::LINE_CHANGE, game, period, time), team(team), LW(LW), C(C), RW(RW), LD(LD), RD(RD) { }
  void print();
  void apply();
private:
  std::string team;
  Player *LW;
  Player *C;
  Player *RW;
  Player *LD;
  Player *RD;
};

#endif // LINECHANGE_HPP

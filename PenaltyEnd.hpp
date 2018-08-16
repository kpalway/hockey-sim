#ifndef PENALTYEND_HPP
#define PENALTYEND_HPP

#include "Event.hpp"
#include "Penalty.hpp"

class PenaltyEnd : public Event {
public:
  PenaltyEnd(Game &game, int period, double time, Penalty *pen): Event(EventType::PENALTY_END, game, period, time), pen(pen) { }
  void print();
  void apply();
private:
  Penalty *pen;
};

#endif // PENALTYEND_HPP

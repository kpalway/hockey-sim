#include "Event.hpp"

#ifndef PERIODEND_HPP
#define PERIODEND_HPP

class PeriodEnd : public Event {
public:
  PeriodEnd(Game &game, int period):
    Event(EventType::PERIOD_END, game, period, 20) { }
  void print();
  void apply();
};

#endif // PERIODEND_HPP

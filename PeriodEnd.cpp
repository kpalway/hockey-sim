#include <iostream>
#include "PeriodEnd.hpp"
#include "Game.hpp"

void PeriodEnd::print() {
  Event::print();
  std::cout << "End of period " << period << std::endl;
}

void PeriodEnd::apply() {
  Event::apply();
  game.NextPeriod();
  game.SetTime(0);
}

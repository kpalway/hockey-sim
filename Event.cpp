#include <iostream>
#include "Event.hpp"
#include "Game.hpp"

void Event::print() {
  std::cout << time << ": ";
}

void Event::apply() {
  game.SetTime(time);
}

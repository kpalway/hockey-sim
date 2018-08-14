#include "Event.hpp"
#include "Game.hpp"

void Event::apply() {
  game.SetTime(time);
}

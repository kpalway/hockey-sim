#include <iostream>
#include "LineChange.hpp"
#include "Player.hpp"
#include "Game.hpp"

void LineChange::print() {
  std::cout << "On-ice for " << team << ": (" << LW->Name() << ", " << C->Name() << ", " << RW->Name()
    << ") (" << LD->Name() << ", " << RD->Name() << ")" << std::endl;
}

void LineChange::apply() {
  Event::apply();
  game.SetActiveLine(team, LW, C, RW, LD, RD);
}

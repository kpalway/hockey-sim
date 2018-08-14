#include <iostream>
#include "Shot.hpp"
#include "Player.hpp"

void Shot::print() {
  std::cout << "Shot by " << shooter->Name() << " saved by " << goalie->Name() << std::endl;
}

void Shot::apply() {
  Event::apply();
}

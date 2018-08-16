#include <iostream>
#include "PenaltyEnd.hpp"
#include "Game.hpp"

void PenaltyEnd::print() {
  std::cout << "Penalty Ended" << std::endl;
}

void PenaltyEnd::apply() {
  Event::apply();
  game.SetEvenStrength();
  game.RemovePenalty(pen);
}

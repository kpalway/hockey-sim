#include <iostream>
#include "Penalty.hpp"
#include "Player.hpp"

void Penalty::print() {
  std::cout << "Minor penalty to " << offender->Name() << std::endl;
}

void Penalty::apply() {
  Event::apply();
  // TODO
}

double Penalty::Remaining() {
  return remaining;
}

#include <iostream>
#include "Penalty.hpp"
#include "Player.hpp"
#include "Game.hpp"

void Penalty::print() {
  Event::print();
  std::cout << "Minor penalty to " << team << ": " << offender->Name() << std::endl;
}

void Penalty::apply() {
  Event::apply();
  game.AddPenalty(this);
  game.SetPowerPlay(!game.IsHome(team));
}

double Penalty::Remaining() {
  return remaining;
}

void Penalty::RemoveTime(double time) {
  remaining -= time;
  if (remaining < 0) {
    remaining = 0;
  }
}

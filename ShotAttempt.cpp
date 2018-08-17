#include <iostream>
#include "ShotAttempt.hpp"
#include "Player.hpp"
#include "Game.hpp"

void ShotAttempt::print() {
  std::cout << "Shot attempt by " << player->Name() << std::endl;
}

void ShotAttempt::apply() {
  Event::apply();
  game.AddShotAttempt(team);
}

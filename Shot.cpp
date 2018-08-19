#include <iostream>
#include "Shot.hpp"
#include "Player.hpp"
#include "Game.hpp"

void Shot::print() {
  std::cout << "Shot by " << shooter->Name() << " saved by " << goalie->Name() << std::endl;
}

void Shot::apply() {
  Event::apply();
  game.AddShot(team);
  shooter->AddShot(sit);
  shooter->AddShotAttempt(sit);
}

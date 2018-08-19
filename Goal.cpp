#include <iostream>
#include "Goal.hpp"
#include "Player.hpp"
#include "Game.hpp"

void Goal::print() {
  Event::print();
  if (sit == Situation::PP) {
    std::cout << "PP ";
  }
  else if (sit == Situation::SH) {
    std::cout << "SH ";
  }
  std::cout << "Goal scored by " << scorer->Name() << " (";
  if (assist1 != NULL && assist2 != NULL) {
    std::cout << assist1->Name() << ", " << assist2->Name();
  }
  else if (assist1 != NULL) {
    std::cout << assist1->Name();
  }
  else {
    std::cout << "Unassisted";
  }
  std::cout << ")" << std::endl;
}

void Goal::apply() {
  Event::apply();

  game.AddGoal(team);

  scorer->AddGoal(sit);
  scorer->AddShot(sit);
  scorer->AddShotAttempt(sit);
  if (assist1 != NULL) {
    assist1->AddFirstAssist(sit);
  }
  if (assist2 != NULL) {
    assist2->AddSecondAssist(sit);
  }

  if (sit == Situation::PP) {
    game.SetEvenStrength();
  }
}

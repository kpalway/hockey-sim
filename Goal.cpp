#include <iostream>
#include "Goal.hpp"
#include "Player.hpp"
#include "Game.hpp"

void Goal::print() {
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

  scorer->ScoreGoal();
  if (assist1 != NULL) {
    assist1->ScoreFirstAssist();
  }
  if (assist2 != NULL) {
    assist2->ScoreSecondAssist();
  }
}

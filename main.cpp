#include <iostream>
#include "PlayerDatabase.hpp"
#include "TeamDatabase.hpp"

int main() {
  std::cout << "No main function implemented as of now." << std::endl;

  PlayerDatabase pdb;
  pdb.initialize();
  TeamDatabase tdb;
  tdb.initialize(pdb);
}

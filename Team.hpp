#include <vector>
#include <string>
#include "Player.hpp"
#include "PlayerDatabase.hpp"

#ifndef TEAM_HPP
#define TEAM_HPP

class Team {
public:
  std::vector<Player*> LW;
  std::vector<Player*> C;
  std::vector<Player*> RW;
  std::vector<Player*> LD;
  std::vector<Player*> RD;
  std::vector<Player*> G;

  Team(std::string name): name(name) { }
  std::string Name();
  void loadTeam(std::string filename, PlayerDatabase &pdb);
private:
  std::string name;
};

#endif // TEAM_HPP

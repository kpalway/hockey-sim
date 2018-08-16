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

  std::vector<Player*> PPLW;
  std::vector<Player*> PPC;
  std::vector<Player*> PPRW;
  std::vector<Player*> PPLD;
  std::vector<Player*> PPRD;

  std::vector<Player*> SHF1;
  std::vector<Player*> SHF2;
  std::vector<Player*> SHLD;
  std::vector<Player*> SHRD;

  Team(std::string name): name(name) { }
  std::string Name();
  bool Ready();
  void loadTeam(std::string filename, PlayerDatabase &pdb);
private:
  std::string name;
};

#endif // TEAM_HPP

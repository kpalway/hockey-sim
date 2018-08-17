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
  bool OnRoster(Player *p);
  void loadTeam(PlayerDatabase &pdb);

  void AddGamePlayed();
private:
  std::vector<Player*> roster;
  void loadFile(PlayerDatabase &pdb, std::vector< std::vector<Player*>* > &vecs, std::string fname, bool special_teams);
  void loadColumn(PlayerDatabase &pdb, std::vector< std::vector<std::string> > &mtx, std::vector<Player*> &vec, uint col, bool special_teams);
  std::string name;
};

#endif // TEAM_HPP

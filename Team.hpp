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

  Team(std::string name): name(name), regulation_wins(0), overtime_wins(0), shootout_wins(0), regulation_losses(0), overtime_losses(0), shootout_losses(0), points(0) { }
  std::string Name();
  bool Ready();
  bool OnRoster(Player *p);
  void loadTeam(PlayerDatabase &pdb);

  void AddGamePlayed();
  void AddRegulationWin();
  void AddOvertimeWin();
  void AddShootoutWin();
  void AddRegulationLoss();
  void AddOvertimeLoss();
  void AddShootoutLoss();
  int Points();
  int Wins();
  int Losses();
  int OvertimeShootoutLosses();

  static void PrintRecordHeading();
  void PrintRecord();
private:
  std::vector<Player*> roster;
  void loadFile(PlayerDatabase &pdb, std::vector< std::vector<Player*>* > &vecs, std::string fname, bool special_teams);
  void loadColumn(PlayerDatabase &pdb, std::vector< std::vector<std::string> > &mtx, std::vector<Player*> &vec, uint col, bool special_teams);
  std::string name;

  int regulation_wins;
  int overtime_wins;
  int shootout_wins;
  int regulation_losses;
  int overtime_losses;
  int shootout_losses;
  int points;
};

#endif // TEAM_HPP

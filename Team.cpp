#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Team.hpp"
#include "CSV.hpp"

std::string Team::Name() {
  return name;
}

bool Team::Ready() {
  if (LW.size() < 4 || C.size() < 4 || RW.size() < 4 || LD.size() < 3
        || RD.size() < 3 || G.size() < 2) {
    return false;
  }
  for (uint i = 0; i < 4; i++) {
    if (!LW[i]->Ready()) {
      return false;
    }
    if (!C[i]->Ready()) {
      return false;
    }
    if (!RW[i]->Ready()) {
      return false;
    }
  }
  for (uint i = 0; i < 3; i++) {
    if (!LD[i]->Ready()) {
      return false;
    }
    if (!RD[i]->Ready()) {
      return false;
    }
  }
  for (uint i = 0; i < 2; i++) {
    if (!G[i]->Ready()) {
      return false;
    }
  }
  if (PPLW.size() < 2 || PPC.size() < 2 || PPRW.size() < 2 || PPLD.size() < 2 || PPRD.size() < 2) {
    return false;
  }
  if (SHF1.size() < 2 || SHF2.size() < 2 || SHLD.size() < 2 || SHRD.size() < 2) {
    return false;
  }
  return true;
}

bool Team::OnRoster(Player *p) {
  return roster.end() != std::find(roster.begin(), roster.end(), p);
}

static bool NonEmptyCell(std::vector<std::string> &row, uint cell) {
  return row.size() > cell && row[cell].length() > 0;
}

void Team::loadColumn(PlayerDatabase &pdb, std::vector< std::vector<std::string> > &mtx, std::vector<Player*> &vec, uint col, bool special_teams) {
  for (uint i = 0; i < mtx.size(); i++) {
    if (NonEmptyCell(mtx[i], col)) {
      Player *p = &pdb.lookup(mtx[i][col]);
      vec.push_back(p);
      if (!special_teams) {
        roster.push_back(p);
      }
      else {
        // check special teams player is on roster
        if (!OnRoster(p)) {
          std::cerr << p->Name() << " (" << name << ") appears on special teams but not on roster" <<std::endl;
        }
      }
    }
  }
}

void Team::loadFile(PlayerDatabase &pdb, std::vector< std::vector<Player*>* > &vecs, std::string fname, bool special_teams) {
  std::vector< std::vector<std::string> > mtx = CSV::ToMatrix(fname);
  for (uint i = 0; i < vecs.size(); i++) {
    loadColumn(pdb, mtx, *vecs[i], i, special_teams);
  }
}

static std::string roster_prefix = "/u/kpalway/hock/rosters/";

static bool PKTimeCompare(Player *a, Player *b) {
  return a->PKMinutesPerGame() > b->PKMinutesPerGame();
}

static bool notFwd(Player *a) {
  return !a->IsForward();
}

static bool notDef(Player *a) {
  return !a->IsDefense();
}

void Team::loadTeam(PlayerDatabase &pdb) {
  std::vector< std::vector<Player*>* > fwds = { &LW, &C, &RW };
  std::vector< std::vector<Player*>* > defs = { &LD, &RD };
  std::vector< std::vector<Player*>* > goal = { &G };
  std::vector< std::vector<Player*>* > pps =  { &PPLW, &PPC, &PPRW, &PPLD, &PPRD };
  loadFile(pdb, fwds, roster_prefix + name + "_F.csv", false);
  loadFile(pdb, defs, roster_prefix + name + "_D.csv", false);
  loadFile(pdb, goal, roster_prefix + name + "_G.csv", false);
  loadFile(pdb, pps, roster_prefix + name + "_PP.csv", true);

  // Choose penalty killers by simply taking the ones who
  //  have the most penalty kill time per game
  std::vector<Player*> roster2 = roster;
  std::sort(roster2.begin(), roster2.end(), PKTimeCompare);
  std::vector<Player*>::iterator beg = roster2.begin();
  std::vector<Player*>::iterator end = roster2.end();
  end = std::remove_if(beg, end, notFwd);
  SHF1.push_back(*beg);
  SHF2.push_back(*(beg+1));
  SHF1.push_back(*(beg+2));
  SHF2.push_back(*(beg+3));

  roster2 = roster;
  std::sort(roster2.begin(), roster2.end(), PKTimeCompare);
  beg = roster2.begin();
  end = roster2.end();
  end = std::remove_if(beg, end, notDef);
  SHLD.push_back(*beg);
  SHRD.push_back(*(beg+1));
  SHLD.push_back(*(beg+2));
  SHRD.push_back(*(beg+3));
}

void Team::AddGamePlayed() {
  for (uint i = 0; i < roster.size(); i++) {
    if (roster[i] != G[1]) {
      roster[i]->AddGamePlayed();
    }
  }
}

void Team::AddRegulationWin() {
  regulation_wins++;
  points += 2;
}

void Team::AddOvertimeWin() {
  overtime_wins++;
  points += 2;
}

void Team::AddShootoutWin() {
  shootout_wins++;
  points += 2;
}

void Team::AddRegulationLoss() {
  regulation_losses++;
}

void Team::AddOvertimeLoss() {
  overtime_losses++;
  points++;
}

void Team::AddShootoutLoss() {
  shootout_losses++;
  points++;
}

int Team::Points() {
  return points;
}

int Team::Wins() {
  return regulation_wins + overtime_wins + shootout_wins;
}

int Team::Losses() {
  return regulation_losses;
}

int Team::OvertimeShootoutLosses() {
  return overtime_losses + shootout_losses;
}

void Team::PrintRecordHeading() {
  std::cout << "      P  W  L OT" << std::endl;
}

void Team::PrintRecord() {
  std::cout << name << " " << std::setw(3) << Points() << " " << std::setw(2) << Wins() << " " << std::setw(2) << Losses()
    << " " << std::setw(2) << OvertimeShootoutLosses() << std::endl;
}

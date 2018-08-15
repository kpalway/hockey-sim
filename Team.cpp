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
  return true;
}

static bool NonEmptyCell(std::vector<std::string> &row, uint cell) {
  return row.size() > cell && row[cell].length() > 0;
}

void Team::loadTeam(std::string filename, PlayerDatabase &pdb) {
  std::vector< std::vector<std::string> > mtx = CSV::ToMatrix(filename);
  // LWs
  for (uint i = 0; i < mtx.size(); i++) {
    if (NonEmptyCell(mtx[i], 0)) {
      LW.push_back(&pdb.lookup(mtx[i][0]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (NonEmptyCell(mtx[i], 1)) {
      C.push_back(&pdb.lookup(mtx[i][1]));
    }
  }
  for (uint i = 0; i< mtx.size(); i++) {
    if (NonEmptyCell(mtx[i], 2)) {
      RW.push_back(&pdb.lookup(mtx[i][2]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (NonEmptyCell(mtx[i], 3)) {
      LD.push_back(&pdb.lookup(mtx[i][3]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (NonEmptyCell(mtx[i], 4)) {
      RD.push_back(&pdb.lookup(mtx[i][4]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (NonEmptyCell(mtx[i], 5)) {
      G.push_back(&pdb.lookup(mtx[i][5]));
    }
  }
}

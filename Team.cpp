#include "Team.hpp"
#include "CSV.hpp"

std::string Team::Name() {
  return name;
}

void Team::loadTeam(std::string filename, PlayerDatabase &pdb) {
  std::vector< std::vector<std::string> > mtx = CSV::ToMatrix(filename);
  // LWs
  for (uint i = 0; i < mtx.size(); i++) {
    if (mtx[i][0].length() > 0) {
      LW.push_back(&pdb.lookup(mtx[i][0]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (mtx[i][1].length() > 0) {
      C.push_back(&pdb.lookup(mtx[i][1]));
    }
  }
  for (uint i = 0; i< mtx.size(); i++) {
    if (mtx[i][2].length() > 0) {
      RW.push_back(&pdb.lookup(mtx[i][2]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (mtx[i][3].length() > 0) {
      LD.push_back(&pdb.lookup(mtx[i][3]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (mtx[i][4].length() > 0) {
      RD.push_back(&pdb.lookup(mtx[i][4]));
    }
  }
  for (uint i = 0; i < mtx.size(); i++) {
    if (mtx[i][5].length() > 0) {
      G.push_back(&pdb.lookup(mtx[i][5]));
    }
  }
}

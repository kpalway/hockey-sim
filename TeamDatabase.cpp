#include <iostream>
#include <algorithm>
#include "TeamDatabase.hpp"

std::string team_names[] = {
  "ANA", "ARI", "BOS", "BUF",
  "CAR", "CBJ", "CGY", "CHI",
  "COL", "DAL", "DET", "EDM",
  "FLA", "LAK", "MIN", "MTL",
  "NJD", "NSH", "NYI", "NYR",
  "OTT", "PHI", "PIT", "SJS",
  "STL", "TBL", "TOR", "VAN",
  "VGK", "WPG", "WSH"
};

Team &TeamDatabase::lookup(std::string name) {
  if (team_map.find(name) != team_map.end()) {
    return (*team_map.find(name)).second;
  }
  std::cerr << "Team " << name << " was not found" << std::endl;
  exit(1);
  return (*team_map.find(name)).second;
}

void TeamDatabase::initialize(PlayerDatabase &pdb) {
  for (int i = 0; i < NUM_TEAMS; i++) {
    team_map.emplace(team_names[i], team_names[i]);
    (*team_map.find(team_names[i])).second.loadTeam(pdb);
  }
}

static bool TeamCompare(Team *a, Team *b) {
  return a->Points() > b->Points();
}

void TeamDatabase::PrintStandings() {
  std::vector<Team*> teams;
  for (TeamMap::iterator it = team_map.begin(); it != team_map.end(); it++) {
    teams.push_back(&(*it).second);
  }
  std::sort(teams.begin(), teams.end(), TeamCompare);

  Team::PrintRecordHeading();
  for (uint i = 0; i < teams.size(); i++) {
    teams[i]->PrintAvgRecord();
  }
}

void TeamDatabase::ResetStats() {
  for (TeamMap::iterator it = team_map.begin(); it != team_map.end(); it++) {
    it->second.ResetStats();
  }
}

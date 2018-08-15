#include <iostream>
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

std::string TeamDatabase::RosterFilename(std::string team) {
  return "/u/kpalway/hock/rosters/" + team + ".csv";
}

void TeamDatabase::initialize(PlayerDatabase &pdb) {
  for (int i = 0; i < NUM_TEAMS; i++) {
    team_map.emplace(team_names[i], team_names[i]);
    (*team_map.find(team_names[i])).second.loadTeam(RosterFilename(team_names[i]), pdb);
  }
}

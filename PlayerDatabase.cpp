#include <iostream>
#include <algorithm>
#include "PlayerDatabase.hpp"
#include "CSV.hpp"

Player &PlayerDatabase::lookup(std::string name) {
  PlayerMap::iterator res = player_map.find(name);
  if (res != player_map.end()) {
    return res->second;
  }
  std::cerr << "Player " << name << " was not found" << std::endl;
  exit(1);
  return res->second;
}

// the length of years[]
#define PAST_YEARS 2

static std::string years[] = {
  "17-18",
  "16-17"
};

static std::string statsPrefix = "/u/kpalway/hock/stats/";

static std::string biosFile = "bios.csv";

void PlayerDatabase::loadStatFile(std::string year, Situation sit, bool ind) {
  std::string fname = statsPrefix + year + (sit == Situation::PP ? "pp-" :
    (sit == Situation::SH ? "sh-" : "")) + (ind ? "individual" : "on-ice")
    + ".csv";
  std::vector< std::vector<std::string> > inds = CSV::ToMatrix(fname);
  for (uint j = 1; j < inds.size(); j++) {
    std::string name = inds[j][1];
    PlayerMap::iterator p_it = player_map.find(name);
    if (p_it == player_map.end()) {
      continue;
    }
    if (ind) {
      IndividualStats stat;
      stat.loadData(inds[j]);
      p_it->second.addIndividualStats(sit, stat);
    }
    else {
      OnIceStats stat;
      stat.loadData(inds[j]);
      p_it->second.addOnIceStats(sit, stat);
    }
  }
}

void PlayerDatabase::initialize() {
  std::vector< std::vector<std::string> > bios = CSV::ToMatrix(statsPrefix + biosFile);

  // Init player and set bio
  for (uint i = 1; i < bios.size(); i++) {
    std::string name = bios[i][1];
    BioStats stat;
    stat.loadData(bios[i]);
    player_map.emplace(name, name);
    player_map.find(name)->second.setBio(stat);
  }

  // iterate through available years of data
  //  for individual and on-ice stats
  for (int i = 0; i < PAST_YEARS; i++) {
    loadStatFile(years[i], Situation::EV, true);
    loadStatFile(years[i], Situation::EV, false);
    loadStatFile(years[i], Situation::PP, true);
    loadStatFile(years[i], Situation::PP, false);
    loadStatFile(years[i], Situation::SH, true);
    loadStatFile(years[i], Situation::SH, false);
  }
}

void PlayerDatabase::PredictAll(Replacement &repl) {
  for (PlayerMap::iterator it = player_map.begin(); it != player_map.end(); it++) {
    it->second.Predict(repl);
  }
}

void PlayerDatabase::PassDay() {
  for (PlayerMap::iterator it = player_map.begin(); it != player_map.end(); it++) {
    it->second.PassDay();
  }
}

/*static bool PointCompare(std::pair<std::string, Player> const &a, std::pair<std::string, Player> const &b) {
  return a.second.Points() > b.second.Points();
}*/

void PlayerDatabase::PrintIndividualStats() {
  IndividualStats::PrintHeading();
  PlayerMap::iterator beg = player_map.begin();
  PlayerMap::iterator end = player_map.end();
  for ( ; beg != end; beg++) {
    if (beg->second.GamesPlayed() > 0) {
      beg->second.PrintIndividualStats();
    }
  }
}

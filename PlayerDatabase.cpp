#include <iostream>
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

#define PREVIOUS_YEARS 1

static std::string indFiles[] = {
  "17-18individual.csv"
};

static std::string onIceFiles[] = {
  "17-18on-ice.csv"
};

static std::string biosFile = "17-18bios.csv";

std::vector<std::string> PlayerDatabase::IndFiles() {
  std::vector<std::string> files;
  for (int i = 0; i < PREVIOUS_YEARS; i++) {
    files.push_back("/u/kpalway/hock/stats/" + indFiles[i]);
  }
  return files;
}

std::vector<std::string> PlayerDatabase::OnIceFiles() {
  std::vector<std::string> files;
  for (int i = 0; i < PREVIOUS_YEARS; i++) {
    files.push_back("/u/kpalway/hock/stats/" + onIceFiles[i]);
  }
  return files;
}

std::string PlayerDatabase::BioFile() {
  return "/u/kpalway/hock/stats/" + biosFile;
}

void PlayerDatabase::initialize() {
  std::vector< std::vector<std::string> > bios = CSV::ToMatrix(BioFile());

  // Init player and set bio
  for (uint i = 1; i < bios.size(); i++) {
    std::string name = bios[i][1];
    BioStats stat;
    stat.loadData(bios[i]);
    player_map.emplace(name, name);
    player_map.find(name)->second.setBio(stat);
  }

  // individual stats
  std::vector<std::string> ifiles = IndFiles();
  for (uint i = 0; i < ifiles.size(); i++) {
    std::vector< std::vector<std::string> > inds = CSV::ToMatrix(ifiles[i]);
    for (uint j = 1; j < inds.size(); j++) {
      std::string name = inds[j][1];
      IndividualStats stat;
      stat.loadData(inds[j]);
      player_map.find(name)->second.addIndividualStats(stat);
    }
  }

  // on-ice stats
  std::vector<std::string> ofiles = OnIceFiles();
  for (uint i = 0; i < ofiles.size(); i++) {
    std::vector< std::vector<std::string> > on_ices = CSV::ToMatrix(ofiles[i]);
    for (uint j = 1; j < on_ices.size(); j++) {
      std::string name = on_ices[j][1];
      OnIceStats stat;
      stat.loadData(on_ices[j]);
      player_map.find(name)->second.addOnIceStats(stat);
    }
  }
}

void PlayerDatabase::PredictAll() {
  for (PlayerMap::iterator it = player_map.begin(); it != player_map.end(); it++) {
    it->second.Predict();
  }
}

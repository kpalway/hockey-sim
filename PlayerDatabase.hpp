#include <map>
#include <string>
#include "Player.hpp"

#ifndef PLAYERDATABASE_HPP
#define PLAYERDATABASE_HPP

class PlayerDatabase {
  struct StringCompare {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
      return lhs.compare(rhs) < 0;
    }
  };
public:
  Player &lookup(std::string name);
  void initialize();
  void PredictAll();
private:
  typedef std::map<std::string, Player, StringCompare> PlayerMap;
  PlayerMap player_map;
  std::string BioFile();
  std::vector<std::string> IndFiles();
  std::vector<std::string> OnIceFiles();
};

#endif // PLAYERDATABASE_HPP

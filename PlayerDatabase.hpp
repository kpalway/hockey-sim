#ifndef PLAYERDATABASE_HPP
#define PLAYERDATABASE_HPP

#include <map>
#include <string>
#include "Player.hpp"
#include "Situation.hpp"

class Replacement;

class PlayerDatabase {
  struct StringCompare {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
      return lhs.compare(rhs) < 0;
    }
  };
public:
  Player &lookup(std::string name);
  void initialize();
  void PredictAll(Replacement &repl);
  void PassDay();
  void PrintIndividualStats();
  void ResetStats();
private:
  void loadStatFile(std::string year, Situation sit, bool ind);
  typedef std::map<std::string, Player, StringCompare> PlayerMap;
  PlayerMap player_map;
  std::vector<std::string> IndFiles();
  std::vector<std::string> OnIceFiles();
};

#endif // PLAYERDATABASE_HPP

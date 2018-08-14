#include <map>
#include <string>
#include "Team.hpp"

#ifndef TEAMDATABASE_HPP
#define TEAMDATABASE_HPP

class TeamDatabase {
  struct StringCompare {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
      return lhs.compare(rhs) < 0;
    }
  };
public:
  Team &lookup(std::string name);
  void initialize(PlayerDatabase &pdb);
private:
  std::string RosterFilename(std::string team);
  std::map<std::string, Team, StringCompare> team_map;
};

#define NUM_TEAMS 31

#endif // TEAMDATABASE_HPP

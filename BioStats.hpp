#include "Stats.hpp"
#include "Position.hpp"

#ifndef BIOSTATS_HPP
#define BIOSTATS_HPP

class BioStats : public Stats {
public:
  std::vector<Position> &Positions();
  int Age(int year, int month, int day);
  int BirthYear();
  int BirthMonth();
  int BirthDay();
  std::string BirthCity();
  std::string BirthState();
  std::string BirthCountry();
  std::string Nationality();
  int Height();
  int Weight();
  int DraftYear();
  std::string DraftTeam();
  int DraftRound();
  int RoundPick();
  int OverallDraftPosition();

  void loadData(std::vector<std::string> &data);
private:
  std::vector<Position> positions;
  int birth_year, birth_month, birth_day;
  std::string birth_city;
  std::string birth_state;
  std::string birth_country;
  std::string nationality;
  int height;
  int weight;
  int draft_year;
  std::string draft_team;
  int draft_round;
  int round_pick;
  int overall_draft_position;
};

#endif // BIOSTATS_HPP

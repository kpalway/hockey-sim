#include "BioStats.hpp"
#include <boost/algorithm/string.hpp>

std::vector<Position> &BioStats::Positions() {
  return positions;
}

int BioStats::Age(int year, int month, int day) {
  if (birth_month < month || (birth_month == month && birth_day <= day)) {
    return year - birth_year;
  }
  else {
    return year - birth_year - 1;
  }
}

int BioStats::BirthYear() {
  return birth_year;
}

int BioStats::BirthMonth() {
  return birth_month;
}

int BioStats::BirthDay() {
  return birth_day;
}

std::string BioStats::BirthCity() {
  return birth_city;
}

std::string BioStats::BirthState() {
  return birth_state;
}

std::string BioStats::BirthCountry() {
  return birth_country;
}

std::string BioStats::Nationality() {
  return nationality;
}

int BioStats::Height() {
  return height;
}

int BioStats::Weight() {
  return weight;
}

int BioStats::DraftYear() {
  return draft_year;
}

std::string BioStats::DraftTeam() {
  return draft_team;
}

int BioStats::DraftRound() {
  return draft_round;
}

int BioStats::RoundPick() {
  return round_pick;
}

int BioStats::OverallDraftPosition() {
  return overall_draft_position;
}

void BioStats::loadData(std::vector<std::string> &data) {
  std::vector<std::string> str_pos;
  boost::split(str_pos, data[3], boost::is_any_of("/"));
  for (std::vector<std::string>::iterator it = str_pos.begin();
       it != str_pos.end(); std::advance(it, 1)) {
    Position ins;
    if (0 == (*it).compare("LW") || 0 == (*it).compare("L")) {
      ins = Position::LW;
    } else if (0 == (*it).compare("RW") || 0 == (*it).compare("R")) {
      ins = Position::RW;
    } else if (0 == (*it).compare("C")) {
      ins = Position::C;
    } else if (0 == (*it).compare("LD")) {
      ins = Position::LD;
    } else if (0 == (*it).compare("RD")) {
      ins = Position::RD;
    } else if (0 == (*it).compare("D")) {
      ins = Position::D;
    } else if (0 == (*it).compare("G")) {
      ins = Position::G;
    }
    positions.insert(positions.begin(), ins);
  }

  std::vector<std::string> str_dob;
  boost::split(str_dob, data[5], boost::is_any_of("-"));
  birth_year = std::stoi(str_dob[0]);
  birth_month = std::stoi(str_dob[1]);
  birth_day = std::stoi(str_dob[2]);

  birth_city = data[6];
  birth_state = data[7];
  birth_country = data[8];
  nationality = data[9];
  height = std::stoi(data[10]);
  weight = std::stoi(data[11]);
  if (!(0 == data[12].compare("-"))) {
    draft_year = std::stoi(data[12]);
    draft_team = data[13];
    draft_round = std::stoi(data[14]);
    round_pick = std::stoi(data[15]);
    overall_draft_position = std::stoi(data[16]);
  }
  else {
    draft_year = 0;
  }
}

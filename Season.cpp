#include <ctime>
#include <boost/algorithm/string.hpp>
#include "Season.hpp"
#include "CSV.hpp"

static const time_t seconds_per_day = 24 * 60 * 60;

void Date::AddDay() {
  struct tm dt;
  dt.tm_year = year - 1900;
  dt.tm_mon = month - 1;
  dt.tm_mday = day;
  time_t sec = mktime(&dt);
  sec += seconds_per_day;
  dt = *localtime(&sec);
  year = dt.tm_year + 1900;
  month = dt.tm_mon + 1;
  day = dt.tm_mday;
}

void Season::loadSeason() {
  std::string fname = "/u/kpalway/hock/schedule/" + year + ".csv";
  std::vector< std::vector<std::string> > mtx = CSV::ToMatrix(fname);
  for (uint i = 0; i < mtx.size(); i++) {
    std::vector<std::string> date_str;
    boost::split(date_str, mtx[i][0], boost::is_any_of("-"));
    Date d;
    d.year = stoi(date_str[0]);
    d.month = stoi(date_str[1]);
    d.day = stoi(date_str[2]);
    schedule.push_back(std::make_tuple(d, mtx[i][3], mtx[i][2]));
  }
}

Schedule Season::DaySchedule(Date d) {
  Schedule result;
  for (uint i = 0; i < schedule.size(); i++) {
    if (std::get<0>(schedule[i]) == d) {
      result.push_back(schedule[i]);
    }
  }
  return result;
}

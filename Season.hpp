#ifndef SEASON_HPP
#define SEASON_HPP

#include <vector>
#include <string>
#include <tuple>

struct Date {
  int year;
  int month;
  int day;
  void AddDay();
  friend bool operator==(Date &d1, Date &d2) {
    return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day;
  }
};

typedef std::tuple<Date, std::string, std::string> Match;
typedef std::vector<Match> Schedule;

class Season {
public:
  Season(std::string year): year(year) { }
  void loadSeason();
  Schedule DaySchedule(Date d);

private:
  std::string year;
  Schedule schedule;
};

#endif // SEASON_HPP

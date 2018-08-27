#ifndef TEAMSTATS_HPP
#define TEAMSTATS_HPP

class TeamStats {
public:
  TeamStats(): regulation_wins(0), overtime_wins(0), shootout_wins(0), regulation_losses(0),
    overtime_losses(0), shootout_losses(0), points(0) { }
  int regulation_wins;
  int overtime_wins;
  int shootout_wins;
  int regulation_losses;
  int overtime_losses;
  int shootout_losses;
  int points;
};

#endif // TEAMSTATS_HPP

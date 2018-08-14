#include "IndividualStats.hpp"

int IndividualStats::GamesPlayed() {
  return games_played;
}

double IndividualStats::TimeOnIce() {
  return time_on_ice;
}

int IndividualStats::Goals() {
  return goals;
}

int IndividualStats::Assists() {
  return first_assists + second_assists;
}

int IndividualStats::FirstAssists() {
  return first_assists;
}

int IndividualStats::SecondAssists() {
  return second_assists;
}

int IndividualStats::Points() {
  return goals + first_assists + second_assists;
}

int IndividualStats::PrimaryPoints() {
  return goals + first_assists;
}

int IndividualStats::Shots() {
  return shots;
}

double IndividualStats::ShootingPercentage() {
  return shooting_percentage;
}

int IndividualStats::ShotAttempts() {
  return shot_attempts;
}

int IndividualStats::UnblockedShotAttempts() {
  return unblocked_shot_attempts;
}

int IndividualStats::ScoringChances() {
  return scoring_chances;
}

int IndividualStats::HighDangerScoringChances() {
  return high_danger_scoring_chances;
}

int IndividualStats::RushAttempts() {
  return rush_attempts;
}

int IndividualStats::ReboundsCreated() {
  return rebounds_created;
}

int IndividualStats::PenaltyMinutes() {
  return penalty_minutes;
}

int IndividualStats::Penalties() {
  return minor_penalties + major_penalties + misconducts;
}

int IndividualStats::MinorPenalties() {
  return minor_penalties;
}

int IndividualStats::MajorPenalties() {
  return major_penalties;
}

int IndividualStats::Misconducts() {
  return misconducts;
}

int IndividualStats::PenaltiesDrawn() {
  return penalties_drawn;
}

int IndividualStats::Giveaways() {
  return giveaways;
}

int IndividualStats::Takeaways() {
  return takeaways;
}

int IndividualStats::Hits() {
  return hits;
}

int IndividualStats::HitsTaken() {
  return hits_taken;
}

int IndividualStats::ShotsBlocked() {
  return shots_blocked;
}

int IndividualStats::FaceoffsWon() {
  return faceoffs_won;
}

int IndividualStats::FaceoffsLost() {
  return faceoffs_lost;
}

double IndividualStats::FaceoffPercentage() {
  return 100 * ((double)faceoffs_won)/(faceoffs_won + faceoffs_lost);
}

void IndividualStats::loadData(std::vector<std::string> &data) {
  games_played = std::stoi(data[4]);
  time_on_ice = std::stod(data[5]);
  goals = std::stoi(data[6]);
  first_assists = std::stoi(data[8]);
  second_assists = std::stoi(data[9]);
  shots = std::stoi(data[11]);
  shooting_percentage = std::stod(data[12]);
  shot_attempts = std::stoi(data[13]);
  unblocked_shot_attempts = std::stoi(data[14]);
  scoring_chances = std::stoi(data[15]);
  high_danger_scoring_chances = std::stoi(data[16]);
  rush_attempts = std::stoi(data[17]);
  rebounds_created = std::stoi(data[18]);
  penalty_minutes = std::stoi(data[19]);
  minor_penalties = std::stoi(data[21]);
  major_penalties = std::stoi(data[22]);
  misconducts = std::stoi(data[23]);
  penalties_drawn = std::stoi(data[24]);
  giveaways = std::stoi(data[25]);
  takeaways = std::stoi(data[26]);
  hits = std::stoi(data[27]);
  hits_taken = std::stoi(data[28]);
  shots_blocked = std::stoi(data[29]);
  faceoffs_won = std::stoi(data[30]);
  faceoffs_lost = std::stoi(data[31]);
}

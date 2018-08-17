#include <iostream>
#include <iomanip>
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

void IndividualStats::AddStats(IndividualStats &other) {
  games_played += other.games_played;
  time_on_ice += other.time_on_ice;
  goals += other.goals;
  first_assists += other.first_assists;
  second_assists += other.second_assists;
  shots += other.shots;
  shot_attempts += other.shot_attempts;
  unblocked_shot_attempts += other.unblocked_shot_attempts;
  scoring_chances += other.scoring_chances;
  high_danger_scoring_chances += other.high_danger_scoring_chances;
  rush_attempts += other.rush_attempts;
  rebounds_created += other.rebounds_created;
  penalty_minutes += other.penalty_minutes;
  minor_penalties += other.minor_penalties;
  major_penalties += other.major_penalties;
  misconducts += other.misconducts;
  penalties_drawn += other.penalties_drawn;
  giveaways += other.giveaways;
  takeaways += other.takeaways;
  hits += other.hits;
  hits_taken += other.hits_taken;
  shots_blocked += other.shots_blocked;
  faceoffs_won += other.faceoffs_won;
  faceoffs_lost += other.faceoffs_lost;
}

void IndividualStats::AddGamePlayed() {
  games_played++;
}

void IndividualStats::AddTimeOnIce(double time) {
  time_on_ice += time;
}

void IndividualStats::AddShotAttempt() {
  shot_attempts++;
}

void IndividualStats::AddShot() {
  shots++;
}

void IndividualStats::AddGoal() {
  goals++;
}

void IndividualStats::AddFirstAssist() {
  first_assists++;
}

void IndividualStats::AddSecondAssist() {
  second_assists++;
}

void IndividualStats::AddPenalty() {
  minor_penalties++;
  penalty_minutes += 2;
}

void IndividualStats::PrintHeading() {
  std::cout << std::setw(30) << "Player" << std::setw(4) << "GP" << 
    std::setw(8) << "TOI" << std::setw(4) << "G" <<
    std::setw(4) << "A" << std::setw(4) << "P" << std::setw(4) << "S" <<
    std::setw(4) << "SA" << std::setw(4) << "PIM" << std::endl;
}

void IndividualStats::Print(std::string player) {
  std::cout << std::setw(30) << player << std::setw(4) << games_played <<
    std::setw(8) << std::fixed << std::setprecision(2) << time_on_ice << std::setw(4) << goals << std::setw(4) << (first_assists+second_assists) << std::setw(4) << (goals+first_assists+second_assists) << std::setw(4) << shots << std::setw(4) << shot_attempts << std::endl;
}

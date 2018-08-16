#include "OnIceStats.hpp"

int OnIceStats::ShotAttempts() {
  return shot_attempts;
}

int OnIceStats::ShotAttemptsAgainst() {
  return shot_attempts_against;
}

double OnIceStats::ShotAttemptShare() {
  return 100 * ((double)shot_attempts)/(shot_attempts + shot_attempts_against);
}

int OnIceStats::UnblockedShotAttempts() {
  return unblocked_shot_attempts;
}

int OnIceStats::UnblockedShotAttemptsAgainst() {
  return unblocked_shot_attempts_against;
}

double OnIceStats::UnblockedShotAttemptShare() {
  return 100 * ((double)unblocked_shot_attempts)/(unblocked_shot_attempts + unblocked_shot_attempts_against);
}

int OnIceStats::Shots() {
  return shots;
}

int OnIceStats::ShotsAgainst() {
  return shots_against;
}

double OnIceStats::ShotShare() {
  return 100 * ((double)shots)/(shots + shots_against);
}

int OnIceStats::Goals() {
  return goals;
}

int OnIceStats::GoalsAgainst() {
  return goals_against;
}

double OnIceStats::GoalShare() {
  return 100 * ((double)goals)/(goals + goals_against);
}

int OnIceStats::ScoringChances() {
  return scoring_chances;
}

int OnIceStats::ScoringChancesAgainst() {
  return scoring_chances_against;
}

double OnIceStats::ScoringChanceShare() {
  return 100 * ((double)scoring_chances)/(scoring_chances + scoring_chances_against);
}

int OnIceStats::HighDangerScoringChances() {
  return high_danger_scoring_chances;
}

int OnIceStats::HighDangerScoringChancesAgainst() {
  return high_danger_scoring_chances_against;
}

double OnIceStats::HighDangerScoringChanceShare() {
  return 100 * ((double)high_danger_scoring_chances)/(high_danger_scoring_chances + high_danger_scoring_chances_against);
}

int OnIceStats::HighDangerGoals() {
  return high_danger_goals;
}

int OnIceStats::HighDangerGoalsAgainst() {
  return high_danger_goals_against;
}

double OnIceStats::HighDangerGoalShare() {
  return 100 * ((double)high_danger_goals)/(high_danger_goals + high_danger_goals_against);
}

double OnIceStats::OnIceShootingPercentage() {
  return 100 * ((double)goals) / shots;
}

double OnIceStats::OnIceSavePercentage() {
  return 100 * (1 - ((double)goals_against)/shots_against);
}

double OnIceStats::PDO() {
  return ((double)goals)/shots + ((double)goals_against)/shots_against;
}

int OnIceStats::OffensiveZoneFaceoffs() {
  return offensive_zone_faceoffs;
}

int OnIceStats::NeutralZoneFaceoffs() {
  return neutral_zone_faceoffs;
}

int OnIceStats::DefensiveZoneFaceoffs() {
  return defensive_zone_faceoffs;
}

double OnIceStats::OffensiveZoneFaceoffPercentage() {
  return ((double)offensive_zone_faceoffs)/(offensive_zone_faceoffs + neutral_zone_faceoffs + defensive_zone_faceoffs);
}

void OnIceStats::loadData(std::vector<std::string> &data) {
  shot_attempts = std::stoi(data[6]);
  shot_attempts_against = std::stoi(data[7]);
  unblocked_shot_attempts = std::stoi(data[9]);
  unblocked_shot_attempts_against = std::stoi(data[10]);
  shots = std::stoi(data[12]);
  shots_against = std::stoi(data[13]);
  goals = std::stoi(data[15]);
  goals_against = std::stoi(data[16]);
  scoring_chances = std::stoi(data[18]);
  scoring_chances_against = std::stoi(data[19]);
  high_danger_scoring_chances = std::stoi(data[21]);
  high_danger_scoring_chances_against = std::stoi(data[22]);
  high_danger_goals = std::stoi(data[24]);
  high_danger_goals_against = std::stoi(data[25]);
  offensive_zone_faceoffs = std::stoi(data[30]);
  neutral_zone_faceoffs = std::stoi(data[31]);
  defensive_zone_faceoffs = std::stoi(data[32]);
}

void OnIceStats::AddStats(OnIceStats &other) {
  shot_attempts += other.shot_attempts;
  shot_attempts_against += other.shot_attempts_against;
  unblocked_shot_attempts += other.unblocked_shot_attempts;
  unblocked_shot_attempts_against += other.unblocked_shot_attempts_against;
  shots += other.shots;
  shots_against += other.shots_against;
  goals += other.goals;
  goals_against += other.goals_against;
  scoring_chances += other.scoring_chances;
  scoring_chances_against += other.scoring_chances_against;
  high_danger_scoring_chances += other.high_danger_scoring_chances;
  high_danger_scoring_chances_against += other.high_danger_scoring_chances_against;
  high_danger_goals += other.high_danger_goals;
  high_danger_goals_against += other.high_danger_goals_against;
  offensive_zone_faceoffs += other.offensive_zone_faceoffs;
  neutral_zone_faceoffs += other.neutral_zone_faceoffs;
  defensive_zone_faceoffs += other.defensive_zone_faceoffs;
}

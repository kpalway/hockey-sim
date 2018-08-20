#include "Probability.hpp"
#include <random>
#include <chrono>

static std::default_random_engine RNG;

void Probability::initialize() {
  RNG = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
}

bool Probability::TrueWithProbability(double prob) {
  std::uniform_real_distribution<double> dist(0, 1);
  return dist(RNG) <= prob;
}

double Probability::DrawFromExp(double lambda) {
  std::exponential_distribution<double> dist(lambda);
  return dist(RNG);
}

unsigned int Probability::DrawFromDiscrete(std::vector<double> &probs) {
  std::discrete_distribution<uint> dist(probs.begin(), probs.end());
  return dist(RNG);
}

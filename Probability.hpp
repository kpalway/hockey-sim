#ifndef PROBABILITY_HPP
#define PROBABILITY_HPP

#include <vector>
#include <utility>

namespace Probability {
  void initialize();
  bool TrueWithProbability(double prob);
  double DrawFromExp(double lambda);
  unsigned int DrawFromDiscrete(std::vector<double> &probs);
};

#endif // PROBABILITY_HPP

#include "constructs/include/epsilon_greedy.h"

using mnyrve::math::UniformDistribution;
using mnyrve::math::Sampler;

namespace mnyrve {
namespace constructs {

EpsilonGreedy::EpsilonGreedy(double epsilon) {
  
  MN_REQUIRE(((epsilon >= 0) && (epsilon <= 1)),
      "Epsilon should be in (0, 1)"); 
  epsilon_ = epsilon;
}

double EpsilonGreedy::GetEpsilon() {
  return epsilon_;
}

void EpsilonGreedy::SetEpsilon(double epsilon) {
  epsilon_ = epsilon;
}

bool EpsilonGreedy::ActGreedy() {

  Sampler sampler(std::make_unique<UniformDistribution>(0, 1), 0, 1);

  if (sampler.SampleValue() > epsilon_) {
    return true;
  } else {
    return false;
  }
}

} // namespace constructs 
} // namespace mnyrve






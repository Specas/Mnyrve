#include "constructs/include/epsilon_greedy.h"

namespace mnyrve {
namespace constructs {

using mnyrve::math::UniformDistribution;
using mnyrve::math::Sampler;

EpsilonGreedy::EpsilonGreedy(double epsilon):
  epsilon_(epsilon),
  sampler_(std::make_unique<UniformDistribution>(0, 1), 0, 1) {
  
    MN_REQUIRE(((epsilon >= 0) && (epsilon <= 1)),
        "Epsilon should be in (0, 1)"); 
}

double EpsilonGreedy::GetEpsilon() {
  return epsilon_;
}

void EpsilonGreedy::SetEpsilon(double epsilon) {
  epsilon_ = epsilon;
}

bool EpsilonGreedy::ActGreedy() {

  if (sampler_.SampleValue() > epsilon_) {
    return true;
  } else {
    return false;
  }
}

} // namespace constructs 
} // namespace mnyrve






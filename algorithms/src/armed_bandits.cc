#include "algorithms/include/armed_bandits.h"

using mnyrve::math::IncrementalAverage;
using mnyrve::common::types::ProcessType;

namespace mnyrve {
namespace algorithms {

ArmedBandits::ArmedBandits(int k, double alpha, double epsilon):
  alpha_(alpha), cumulative_reward_(0), 
  average_manager_(ProcessType::kNonStationary, k) {

    MN_REQUIRE((k>0), "k must be positive");
    k_ = k;

    MN_REQUIRE(((epsilon >= 0) && (epsilon <= 1)),
        "Epsilon should be in (0, 1)");
    epsilon_= epsilon;

    action_value_ = Eigen::VectorXd::Zero(k);
    action_frequency_ = Eigen::VectorXd::Zero(k);

}

int ArmedBandits::GetK() {
  return k_;
}

double ArmedBandits::GetAlpha() {
  return alpha_;
}

double ArmedBandits::GetEpsilon() {
  return epsilon_;
}

double ArmedBandits::GetCumulativeReward() {
  return cumulative_reward_;
}

void ArmedBandits::SetAlpha(double alpha) {
  alpha_ = alpha;
}

void ArmedBandits::SetEpsilon(double epsilon) {
  epsilon_ = epsilon;
}






} // namespace algorithms
} // namespace mnyrve

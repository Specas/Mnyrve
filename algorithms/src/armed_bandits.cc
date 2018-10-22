#include "algorithms/include/armed_bandits.h"

using mnyrve::common::types::ProcessType;
using mnyrve::common::types::MaxMatrixType;
using mnyrve::constructs::EpsilonGreedy;
using mnyrve::math::MaxOrRandom;
using mnyrve::math::IncrementalAverage;

using Eigen::VectorXd;

using VectorXi = Eigen::Matrix<int, Eigen::Dynamic, 1>;

namespace mnyrve {
namespace algorithms {

ArmedBandits::ArmedBandits(int k, double alpha, double epsilon):
  k_(k), alpha_(alpha), epsilon_(epsilon), steps_(0), 
  cumulative_reward_(0), 
  action_frequency_(VectorXi::Zero(k)),
  average_manager_(ProcessType::kNonStationary, Eigen::VectorXd::Zero(k)), 
  epsilon_greedy_(epsilon) {

    MN_REQUIRE((k>0), "k must be positive");

    MN_REQUIRE(((epsilon >= 0) && (epsilon <= 1)),
        "Epsilon should be in (0, 1)");

    average_manager_.SetStepSize(alpha);

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

int ArmedBandits::GetSteps() {
  return steps_;
}

double ArmedBandits::GetCumulativeReward() {
  return cumulative_reward_;
}

VectorXd ArmedBandits::GetActionValue() {
  return average_manager_.GetAverages();
}

VectorXi ArmedBandits::GetActionFrequency() {
  return action_frequency_;
}


void ArmedBandits::SetAlpha(double alpha) {
  alpha_ = alpha;
}

void ArmedBandits::SetEpsilon(double epsilon) {

  MN_REQUIRE(((epsilon >= 0) && (epsilon <= 1)),
      "Epsilon should be in (0, 1)");
  epsilon_ = epsilon;

}

int ArmedBandits::TakeAction() {

  if (epsilon_greedy_.ActGreedy()) {
    
     MaxMatrixType<double> max_matrix_type =
       MaxOrRandom<double>(average_manager_.GetAverages());
     return max_matrix_type.maximum_ind.first;

  } else {

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> ud(0, k_ - 1); 
    return ud(generator);

  } 

}


void ArmedBandits::RegisterReward(int index, double reward) {

  MN_REQUIRE(((index >= 0) && (index < k_)), "");

  // For the first time we update an average, we copy it directly.
  // The first update must not use the step size
  
  if (action_frequency_(index) == 0) {
    average_manager_.SetAverages(index, reward);
  } else {
    average_manager_.Update(index, reward);
  }

  steps_ += 1;
  cumulative_reward_ += reward;
  action_frequency_(index) += 1;

}


} // namespace algorithms
} // namespace mnyrve

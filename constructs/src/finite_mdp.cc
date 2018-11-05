#include "constructs/include/finite_mdp.h"

namespace mnyrve {
namespace constructs {

using Eigen::MatrixXd;
using mnyrve::math::IsStochasticMatrix;
using mnyrve::math::IsSquare;
using mnyrve::math::Tensor3;

FiniteMDP::FiniteMDP(int num_states, int num_actions, double gamma):
  num_states_(num_states), num_actions_(num_actions), gamma_(gamma),
  state_transition_tensor_(num_actions, num_states, num_states), 
  expected_rewards_(MatrixXd::Zero(num_states, num_actions)) {}


FiniteMDP::FiniteMDP(Tensor3<double> state_transition_tensor, 
                     int num_actions, 
                     double gamma):
  num_states_(state_transition_tensor.rows()),
  num_actions_(state_transition_tensor.depth()), gamma_(gamma), 
  state_transition_tensor_(state_transition_tensor), 
  expected_rewards_(MatrixXd::Zero(num_states_, num_actions_)) {

    MN_REQUIRE((state_transition_tensor.depth() == num_actions), 
        "The length of the first dimension must match num_actions");
    for (int i = 0; i < num_actions; i++) {
      MN_REQUIRE(IsSquare(state_transition_tensor(i)), 
            "Each state transition matrix must be square.");
      MN_REQUIRE(IsStochasticMatrix(state_transition_tensor(i)), 
          "The rows of each state transition matrix must sum to one.");
    }
}

FiniteMDP::FiniteMDP(Tensor3<double> state_transition_tensor, 
                     int num_actions, 
                     MatrixXd expected_rewards, 
                     double gamma):
  num_states_(state_transition_tensor.rows()),
  num_actions_(state_transition_tensor.depth()), gamma_(gamma), 
  state_transition_tensor_(state_transition_tensor), 
  expected_rewards_(expected_rewards) {

    MN_REQUIRE((state_transition_tensor.depth() == num_actions), 
        "The length of the first dimension must match num_actions");
    for (int i = 0; i < num_actions; i++) {
      MN_REQUIRE(IsSquare(state_transition_tensor(i)), 
            "Each state transition matrix must be square.");
      MN_REQUIRE(IsStochasticMatrix(state_transition_tensor(i)), 
          "The rows of each state transition matrix must sum to one.");
    }
    MN_REQUIRE(((expected_rewards.rows() == num_states_) &&
          (expected_rewards.cols() == num_actions_)), 
        "Incorrect expected rewards dimensions");

}

int FiniteMDP::GetNumStates() {
  return num_states_;
}

int FiniteMDP::GetNumActions() {
  return num_actions_;
}

double FiniteMDP::GetGamma() {
  return gamma_;
}

Tensor3<double> FiniteMDP::GetStateTransitionTensor() {
  return state_transition_tensor_;
}

MatrixXd FiniteMDP::GetExpectedRewards() {
  return expected_rewards_;
}

void FiniteMDP::SetGamma(double gamma) {
  gamma_ = gamma;
}

void FiniteMDP::SetStateTransitionTensor(
    Tensor3<double> state_transition_tensor) {

    MN_REQUIRE((state_transition_tensor.depth() == num_actions_), 
        "The length of the first dimension must match num_actions");
    for (int i = 0; i < num_actions_; i++) {
      MN_REQUIRE(IsSquare(state_transition_tensor(i)), 
            "Each state transition matrix must be square.");
      MN_REQUIRE(IsStochasticMatrix(state_transition_tensor(i)), 
          "The rows of each state transition matrix must sum to one.");
    }

  state_transition_tensor_ = state_transition_tensor;

}

void FiniteMDP::SetExpectedRewards(MatrixXd expected_rewards) {

  MN_REQUIRE(((expected_rewards.rows() == num_states_) &&
        (expected_rewards.cols() == num_actions_)), 
        "Incorrect expected rewards dimensions");
  expected_rewards_ = expected_rewards;

}



} // namespace constructs
} // namespace mnyrve

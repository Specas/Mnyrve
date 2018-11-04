#include "constructs/include/finite_mdp.h"


using Eigen::MatrixXd;
using mnyrve::math::IsStochasticMatrix;
using mnyrve::math::IsSquare;
using mnyrve::math::Tensor3;


namespace mnyrve {
namespace constructs {

FiniteMDP::FiniteMDP(int num_states, int num_actions, double gamma):
  num_states_{num_states}, num_actions_{num_actions}, gamma_{gamma},
  state_transition_tensor_{num_actions, num_states, num_states}, 
  expected_rewards_{MatrixXd::Zero(num_states, num_actions)} {}


FiniteMDP::FiniteMDP(Tensor3<double> state_transition_tensor, 
                     int num_actions, 
                     double gamma):
  num_states_{state_transition_tensor.rows()},
  num_actions_{state_transition_tensor.depth()}, gamma_{gamma}, 
  state_transition_tensor_{state_transition_tensor}, 
  expected_rewards_{MatrixXd::Zero(num_states_, num_actions_)} {

    for (int i = 0; i < num_states_; i++) {
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
  num_states_{state_transition_tensor.rows()},
  num_actions_{state_transition_tensor.depth()}, gamma_{gamma}, 
  state_transition_tensor_{state_transition_tensor}, 
  expected_rewards_{expected_rewards} {

    for (int i = 0; i < num_states_; i++) {
      MN_REQUIRE(IsSquare(state_transition_tensor(i)), 
            "Each state transition matrix must be square.");
      MN_REQUIRE(IsStochasticMatrix(state_transition_tensor(i)), 
          "The rows of each state transition matrix must sum to one.");
    }

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



} // namespace constructs
} // namespace mnyrve

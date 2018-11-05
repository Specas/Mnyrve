#include "constructs/include/finite_policy.h"

namespace mnyrve {
namespace constructs {

using Eigen::MatrixXd;

FinitePolicy::FinitePolicy(int num_states, int num_actions):
  num_states_(num_states), num_actions_(num_actions), 
  policy_matrix_(MatrixXd::Zero(num_states, num_actions)) {}

FinitePolicy::FinitePolicy(MatrixXd policy_matrix):
  num_states_(policy_matrix.rows()), num_actions_(policy_matrix.cols()), 
  policy_matrix_(policy_matrix) {}

int FinitePolicy::GetNumStates() {
  return num_states_;
}

int FinitePolicy::GetNumActions() {
  return num_actions_;
}

MatrixXd FinitePolicy::GetPolicyMatrix() {
  return policy_matrix_;
}

void FinitePolicy::SetPolicyMatrix(Eigen::MatrixXd policy_matrix) {

  MN_REQUIRE(((policy_matrix.rows() == num_states_) &&
        (policy_matrix.cols() == num_actions_)), 
        "Policy matrix dimensions should match state and action dimensions.");

  policy_matrix_ = policy_matrix;

}

} // namespace constructs
} // namespace mnyrve

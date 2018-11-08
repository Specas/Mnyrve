#include "algorithms/include/iterative_policy_evaluation.h"

namespace mnyrve {
namespace algorithms {

using Eigen::MatrixXd;
using Eigen::VectorXd;
using mnyrve::constructs::FiniteMDP;
using mnyrve::constructs::FinitePolicy;
using mnyrve::constructs::FiniteVFunction;

IterativePolicyEvaluation::IterativePolicyEvaluation(
    std::unique_ptr<FiniteMDP> mdp, 
    std::unique_ptr<FinitePolicy> policy):
  mdp_(std::move(mdp)), policy_(std::move(policy)),
  v_function_(FiniteVFunction(policy_->GetNumStates())),
  num_states_(mdp_->GetNumStates()), num_actions_(mdp_->GetNumActions()), 
  gamma_(mdp_->GetGamma()) {

    MN_REQUIRE(((mdp_->GetNumStates() == policy_->GetNumStates()) &&
          (mdp_->GetNumActions() == policy_->GetNumActions())), 
          "MDP and Policy matrices do not match.");
}

int IterativePolicyEvaluation::GetNumStates() {
  return num_states_;
}

int IterativePolicyEvaluation::GetNumActions() {
  return num_actions_;
}

double IterativePolicyEvaluation::GetGamma() {
  return gamma_;
}

VectorXd IterativePolicyEvaluation::GetValueFunctionVector() {
  return v_function_.GetValue();
}

FiniteVFunction IterativePolicyEvaluation::GetValueFunction() {
  return FiniteVFunction(v_function_.GetValue());
}

void IterativePolicyEvaluation::Evaluate(
    double stop_threshold) {

  double value_norm = 0;

  // Computing the policy averaged reward.
  // Being independing of the value function, it can be computed 
  // outside the loop
  VectorXd expected_rewards_pi = (mdp_->GetExpectedRewards().array() *
    policy_->GetPolicyMatrix().array()).matrix().rowwise().sum();

  do {

    // Computing the policy averaged expected value function for the next state
    MatrixXd expected_value(num_states_, num_actions_);

    for (int i = 0; i < num_actions_; i++) {

      expected_value.col(i) = mdp_->GetStateTransitionTensor()(i) * GetValueFunctionVector();

    }

    VectorXd expected_value_pi = (expected_value.array() * 
      policy_->GetPolicyMatrix().array()).matrix().rowwise().sum();

    value_norm = (expected_rewards_pi + gamma_*expected_value_pi - 
        GetValueFunctionVector()).norm();
    v_function_.SetValue(expected_rewards_pi + gamma_*expected_value_pi);

  } while (value_norm > stop_threshold);

}


} // namespace algorithms
} // namespace mnyrve

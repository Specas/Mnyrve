#include "algorithms/include/policy_iteration.h"

namespace mnyrve {
namespace algorithms {

using Eigen::MatrixXd;
using Eigen::VectorXd;
using mnyrve::constructs::FiniteMDP;
using mnyrve::constructs::FinitePolicy;
using mnyrve::constructs::FiniteVFunction;

PolicyIteration::PolicyIteration(
    std::unique_ptr<FiniteMDP> mdp, 
    std::unique_ptr<FinitePolicy> init_policy):
  mdp_(std::move(mdp)), policy_(std::move(init_policy)),
  v_function_(FiniteVFunction(policy_->GetNumStates())),
  num_states_(mdp_->GetNumStates()), num_actions_(mdp_->GetNumActions()), 
  gamma_(mdp_->GetGamma()) {

    MN_REQUIRE(((mdp_->GetNumStates() == policy_->GetNumStates()) &&
          (mdp_->GetNumActions() == policy_->GetNumActions())), 
          "MDP and Policy matrices do not match.");

}

int PolicyIteration::GetNumStates() {
  return num_states_;
}

int PolicyIteration::GetNumActions() {
  return num_actions_;
}

double PolicyIteration::GetGamma() {
  return gamma_;
}

VectorXd PolicyIteration::GetValueFunctionVector() {
  return v_function_.GetValue();
}

FiniteVFunction PolicyIteration::GetValueFunction() {
  return FiniteVFunction(v_function_.GetValue());
}

MatrixXd PolicyIteration::GetPolicyMatrix() {
  return policy_->GetPolicyMatrix();
}

FinitePolicy PolicyIteration::GetPolicy() {
  return FinitePolicy(policy_->GetPolicyMatrix());
}

void PolicyIteration::Evaluate(double stop_threshold) {

  double value_norm{0};
  bool is_policy_stable{false};

  while (!is_policy_stable) {

    // Evaluating the policy first

    // Computing the policy averaged reward.
    // Being independing of the value function, it can be computed 
    // outside the loop
    VectorXd expected_rewards_pi = (mdp_->GetExpectedRewards().array() *
      policy_->GetPolicyMatrix().array()).matrix().rowwise().sum();

    do {

      // Computing the policy averaged expected value function for the next state
      MatrixXd expected_value(num_states_, num_actions_);

      for (int i = 0; i < num_actions_; i++) {
        expected_value.col(i) = mdp_->GetStateTransitionTensor()(i) *
          GetValueFunctionVector();
      }

      VectorXd expected_value_pi = (expected_value.array() * 
        policy_->GetPolicyMatrix().array()).matrix().rowwise().sum();

      value_norm = (expected_rewards_pi + gamma_*expected_value_pi - 
          GetValueFunctionVector()).norm();
      v_function_.SetValue(expected_rewards_pi + gamma_*expected_value_pi);

    } while (value_norm > stop_threshold);


    // Policy improvement
    MatrixXd expected_rewards = mdp_->GetExpectedRewards();
    MatrixXd expected_value(num_states_, num_actions_);

    for (int i = 0; i < num_actions_; i++) {
        expected_value.col(i) = mdp_->GetStateTransitionTensor()(i) * 
          GetValueFunctionVector();
    }

    // New discrete policy
    MatrixXd new_policy_matrix = MatrixXd::Zero(num_states_, num_actions_);
    MatrixXd expected_total = expected_rewards + gamma_*expected_value;
    int max_ind = 0;

    for (int i = 0; i < num_states_; i++) {

        expected_total.row(i).maxCoeff(&max_ind);
        new_policy_matrix(i, max_ind) = 1;

    }

    // Checking if the policy has changed
    if (GetPolicyMatrix().isApprox(new_policy_matrix)) {
      is_policy_stable = true;
    }

    policy_->SetPolicyMatrix(new_policy_matrix);


  }

}


} // namespace algorithms
} // namespace mnyrve

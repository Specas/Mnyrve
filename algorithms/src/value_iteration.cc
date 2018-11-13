#include "algorithms/include/value_iteration.h"

namespace mnyrve {
namespace algorithms {

using Eigen::MatrixXd;
using Eigen::VectorXd;
using mnyrve::constructs::FiniteMDP;
using mnyrve::constructs::FinitePolicy;
using mnyrve::constructs::FiniteVFunction;

ValueIteration::ValueIteration(
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

int ValueIteration::GetNumStates() {
  return num_states_;
}

int ValueIteration::GetNumActions() {
  return num_actions_;
}

double ValueIteration::GetGamma() {
  return gamma_;
}

VectorXd ValueIteration::GetValueFunctionVector() {
  return v_function_.GetValue();
}

FiniteVFunction ValueIteration::GetValueFunction() {
  return FiniteVFunction(v_function_.GetValue());
}

MatrixXd ValueIteration::GetPolicyMatrix() {
  return policy_->GetPolicyMatrix();
}

FinitePolicy ValueIteration::GetPolicy() {
  return FinitePolicy(policy_->GetPolicyMatrix());
}

void ValueIteration::Evaluate(double stop_threshold) {

  double value_norm{0};
  bool is_policy_stable{false};

  // Initializing required Eigen objects
  MatrixXd expected_rewards = mdp_->GetExpectedRewards();
  MatrixXd expected_value(num_states_, num_actions_);
  MatrixXd expected_total;
  MatrixXd new_policy_matrix;
  VectorXd expected_max_total;

  while (!is_policy_stable) {

    // Computing the value function using the Bellman optimality equation
    VectorXd expected_rewards_pi = (mdp_->GetExpectedRewards().array() *
      policy_->GetPolicyMatrix().array()).matrix().rowwise().sum();

    do {

      // The total expected value for each action

      for (int i = 0; i < num_actions_; i++) {
        expected_value.col(i) = mdp_->GetStateTransitionTensor()(i) *
          GetValueFunctionVector();
      }

      expected_total = expected_rewards + gamma_*expected_value;

      value_norm = (expected_total.rowwise().maxCoeff() - 
          GetValueFunctionVector()).norm();
      v_function_.SetValue(expected_total.rowwise().maxCoeff());

    } while (value_norm > stop_threshold);


    // Policy improvement
    for (int i = 0; i < num_actions_; i++) {
        expected_value.col(i) = mdp_->GetStateTransitionTensor()(i) * 
          GetValueFunctionVector();
    }

    // New discrete policy
    new_policy_matrix = MatrixXd::Zero(num_states_, num_actions_);
    expected_total = expected_rewards + gamma_*expected_value;
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

#ifndef FINITE_MDP_H
#define FINITE_MDP_H

#include "common/include/error_macros.h"
#include "math/matrix/include/matrix_checks.h"
#include "math/tensor/include/tensor3.h"
#include "third_party/Eigen/Dense"

#include <iostream>

namespace mnyrve {
namespace constructs {

class FiniteMDP {

  public:
    FiniteMDP(int num_states, int num_actions, double gamma);
    FiniteMDP(mnyrve::math::Tensor3<double> state_transition_tensor,
              int num_actions,
              double gamma);
    FiniteMDP(mnyrve::math::Tensor3<double> state_transition_tensor,
              int num_actions,
              Eigen::MatrixXd expected_rewars, 
              double gamma);

    int GetNumStates();
    int GetNumActions();
    double GetGamma();
    mnyrve::math::Tensor3<double> GetStateTransitionTensor();
    Eigen::MatrixXd GetExpectedRewards();


  private:
    int num_states_;
    int num_actions_;
    double gamma_;
    mnyrve::math::Tensor3<double> state_transition_tensor_;
    Eigen::MatrixXd expected_rewards_;

};


} // namespace constructs
} // namespace mnyrve

#endif

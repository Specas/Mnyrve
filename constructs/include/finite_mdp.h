#ifndef FINITE_MDP_H
#define FINITE_MDP_H

#include "common/include/error_macros.h"
#include "math/matrix/include/matrix_checks.h"
#include "third_party/Eigen/Dense"

#include <iostream>

namespace mnyrve {
namespace constructs {

class FiniteMDP {

  public:
    FiniteMDP(int num_states);
    FiniteMDP(Eigen::MatrixXd state_transition_matrix);

  private:
    int num_states_;
    Eigen::MatrixXd state_transition_matrix_;

};


} // namespace constructs
} // namespace mnyrve

#endif

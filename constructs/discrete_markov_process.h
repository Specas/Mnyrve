#ifndef DISCRETE_MARKOV_PROCESS_H
#define DISCRETE_MARKOV_PROCESS_H

#include "common/error_macros.h"
#include "common/types.h"
#include "math/matrix_checks.h"
#include "third_party/Eigen/Dense"

#include <iostream>

namespace mnyrve {
namespace constructs {

class DiscreteMarkovProcess {

  public:
    DiscreteMarkovProcess(int num_states);
    DiscreteMarkovProcess(Eigen::MatrixXd state_transition_matrix);

  private:
    int num_states_;
    Eigen::MatrixXd state_transition_matrix_;


};


} // namespace constructs
} // namespace mnyrve

#endif

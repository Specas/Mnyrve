#ifndef FINITE_POLICY_H
#define FINITE_POLICY_H

#include "common/include/error_macros.h"
#include "math/matrix/include/matrix_checks.h"
#include "third_party/Eigen/Dense"

namespace mnyrve {
namespace constructs {

class FinitePolicy {

  public: 
    FinitePolicy(int num_states, int num_actions);
    FinitePolicy(Eigen::MatrixXd policy_matrix);

    int GetNumStates();
    int GetNumActions();
    Eigen::MatrixXd GetPolicyMatrix();

    void SetPolicyMatrix(Eigen::MatrixXd policy_matrix);

  private:
    int num_states_;
    int num_actions_;
    Eigen::MatrixXd policy_matrix_;

};


} // namespace constructs
} // namespace mnyrve


#endif

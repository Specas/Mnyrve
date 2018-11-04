#ifndef FINITE_V_FUNCTION_H
#define FINITE_V_FUNCTION_H

#include "common/include/error_macros.h"
#include "third_party/Eigen/Dense"

namespace mnyrve {
namespace constructs {

class FiniteVFunction {

  public:
    FiniteVFunction(int num_states);
    FiniteVFunction(Eigen::VectorXd value);

    int GetNumStates();
    Eigen::VectorXd GetValue();
    void SetValue(Eigen::VectorXd value);

    double& operator()(int ind);

  private:
    int num_states_;
    Eigen::VectorXd value_;

};

} // namespace constructs
} // namespace mnyrve


#endif

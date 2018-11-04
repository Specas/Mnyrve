#ifndef FINITE_Q_FUNCTION_H
#define FINITE_Q_FUNCTION_H

#include "third_party/Eigen/Dense"

namespace mnyrve {
namespace constructs {

class FiniteQFunction {

  public:
    FiniteQFunction(int num_states, int num_actions);
    FiniteQFunction(Eigen::MatrixXd value);

    int GetNumStates();
    int GetNumActions();
    Eigen::MatrixXd GetValue();
    void SetValue();

    double& operator[](int row, int col);


  private:
    int num_states_;
    int num_actions_;
    Eigen::MatrixXd value_;

};

} // namespace constructs
} // namespace mnyrve


#endif

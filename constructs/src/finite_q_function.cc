#include "constructs/include/finite_q_function.h"

namespace mnyrve {
namespace constructs {

FiniteQFunction::FiniteQFunction(int num_states, int num_actions):
  num_states_(num_states), num_actions_(num_actions), 
  value_(Eigen::MatrixXd::Zero(num_states, num_actions)) {}

FiniteQFunction::FiniteQFunction(Eigen::MatrixXd value):
  num_states_(value.rows()), num_actions_(value.cols()), value_(value) {}

int FiniteQFunction::GetNumStates() {
  return num_states_;
}

int FiniteQFunction::GetNumActions() {
  return num_actions_;
}

Eigen::MatrixXd FiniteQFunction::GetValue() {
  return value_;
}

void FiniteQFunction::SetValue(Eigen::MatrixXd value) {

  MN_REQUIRE(((value.rows() == num_states_) && (value.cols() == num_actions_)),

      "The input size must be (num_states x num_actions)");
  value_ = value;

}

double& FiniteQFunction::operator()(int row, int col) {

  return value_(row, col);

}

} // namespace constructs
} // namespace mnyrve



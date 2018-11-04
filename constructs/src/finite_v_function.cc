#include "constructs/include/finite_v_function.h"

namespace mnyrve {
namespace constructs {

FiniteVFunction::FiniteVFunction(int num_states):
  num_states_(num_states), value_(Eigen::VectorXd::Zero(num_states)) {}

FiniteVFunction::FiniteVFunction(Eigen::VectorXd value) {

  MN_REQUIRE((value.cols() == 1), 
      "The input must be a vector (Single column)");

  num_states_ = value.rows();
  value_ = value;

}

int FiniteVFunction::GetNumStates() {
  return num_states_;
}

Eigen::VectorXd FiniteVFunction::GetValue() {
  return value_;
}

void FiniteVFunction::SetValue(Eigen::VectorXd value) {

  MN_REQUIRE((value.cols() == 1), 
      "The input must be a vector (Single column)");
  MN_REQUIRE((value.rows() == num_states_), 
      "The input vector size must match the state size");
  value_ = value;
}

double& FiniteVFunction::operator()(int ind) {

  return value_(ind);

}


} // namespace constructs 
} // namespace mnyrve


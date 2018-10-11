#include "constructs/include/discrete_markov_process.h"


using mnyrve::math::IsStochasticMatrix;
using mnyrve::math::IsSquare;


namespace mnyrve {
namespace constructs {

  DiscreteMarkovProcess::DiscreteMarkovProcess(int num_states):
    num_states_{num_states} {}

  DiscreteMarkovProcess::DiscreteMarkovProcess(
      Eigen::MatrixXd state_transition_matrix) {

  MN_REQUIRE(IsSquare(state_transition_matrix), 
     "The state transition matrix must be a square matrix.");
  MN_REQUIRE(IsStochasticMatrix(state_transition_matrix),
      "The rows of the state transition matrix must sum to one.");

    state_transition_matrix_ = state_transition_matrix;

  }


} // namespace constructs
} // namespace mnyrve

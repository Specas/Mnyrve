#include "algorithms/include/policy_iteration.h"
#include "common/include/error_macros.h"
#include "environments/grid_world/include/grid_world.h"

#include <gflags/gflags.h>
#include <string>
#include <map>

namespace mnyrve {
namespace examples {

using mnyrve::environments::GridWorld;
using mnyrve::algorithms::PolicyIteration;
using mnyrve::math::Tensor3;
using mnyrve::constructs::FiniteMDP;
using mnyrve::constructs::FinitePolicy;
using Eigen::MatrixXd;
using Eigen::VectorXd;

using std::map;
using std::move;
using std::string;

DEFINE_int32(num_states, 25, "Number of cells in the grid");
DEFINE_double(normal_reward, -1, "Reward for taking a normal step");
DEFINE_double(obstacle_reward, -5, "Reward for stepping into an obstacle");
DEFINE_double(goal_reward, 10, "Reward for reaching a goal");

int do_main(int argc, char* argv[]) {

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  // Only considering the four directional actions in this example
  const int num_actions = 4;

  // Sqrt of num_states
  int cells_per_row = std::sqrt(FLAGS_num_states);

  // Creating maps for the actions and states
  map<int, string> action_map = {{0, "left"},
                                 {1, "top"},
                                 {2, "right"}, 
                                 {3, "bottom"}};

  GridWorld grid_world(FLAGS_num_states, 
                       num_actions, 
                       FLAGS_normal_reward, 
                       FLAGS_obstacle_reward, 
                       FLAGS_goal_reward);

  grid_world.SetUp();

  // Setting up the transition tensor, expected reward matrix and policy matrix
  // for iterative policy evaluation
  
  Tensor3<double> state_transition_tensor(
      num_actions, FLAGS_num_states, FLAGS_num_states);
  MatrixXd expected_rewards = MatrixXd::Constant(
      FLAGS_num_states, num_actions, FLAGS_normal_reward);

  // Filling up values in the state transition tensor
  // depending on the cell state

  for (int i = 0; i < FLAGS_num_states; i++) {

    // Corresponding row and col indices
    int row = i/cells_per_row;
    int col = i%cells_per_row;

    // Getting indices of the 4 neighbors
    // For indices out of bounds, these will not be right.
    // They wont be used either
    int left_ind = (row)*cells_per_row + (col - 1);
    int top_ind = (row - 1)*cells_per_row + (col);
    int right_ind = (row)*cells_per_row + (col + 1);
    int bottom_ind = (row + 1)*cells_per_row + (col);

    for (int j = 0; j < num_actions; j++) {


      if (action_map[j] == "left") {

        // Cannot move left in this condition
        if ((col == 0) ||
            (grid_world.GetCellState().at(left_ind) == -1)) {
          state_transition_tensor(j)(i, i) = 1;
        } else {
          state_transition_tensor(j)(i, left_ind) = 1;
        }
        
        // Setting rewards
        if ((col == 0) ||
            (grid_world.GetCellState().at(left_ind) == -1)) {
          expected_rewards(i, j) = FLAGS_obstacle_reward;
        } else if (grid_world.GetCellState().at(left_ind) == 2) {
          // Goal state
          expected_rewards(i, j) = FLAGS_goal_reward;
        } else {
          // Normal transition
          expected_rewards(i, j) = FLAGS_normal_reward;
        }


      } else if (action_map[j] == "top") {

        // Cannot move top in this condition
        if ((row == 0) ||
            (grid_world.GetCellState().at(top_ind) == -1)) {
          state_transition_tensor(j)(i, i) = 1;
        } else {
          state_transition_tensor(j)(i, top_ind) = 1;
        }

        // Setting rewards
        if ((row == 0) ||
            (grid_world.GetCellState().at(top_ind) == -1)) {
          expected_rewards(i, j) = FLAGS_obstacle_reward;
        } else if (grid_world.GetCellState().at(top_ind) == 2) {
          // Goal state
          expected_rewards(i, j) = FLAGS_goal_reward;
        } else {
          // Normal transition
          expected_rewards(i, j) = FLAGS_normal_reward;
        }


      } else if (action_map[j] == "right") {

        // Cannot move right in this condition
        if ((col == cells_per_row - 1) ||
            (grid_world.GetCellState().at(right_ind) == -1)) {
          state_transition_tensor(j)(i, i) = 1;
        } else {
          state_transition_tensor(j)(i, right_ind) = 1;
        }

        // Setting rewards
        if ((col == cells_per_row - 1) ||
            (grid_world.GetCellState().at(right_ind) == -1)) {
          expected_rewards(i, j) = FLAGS_obstacle_reward;
        } else if (grid_world.GetCellState().at(right_ind) == 2) {
          // Goal state
          expected_rewards(i, j) = FLAGS_goal_reward;
        } else {
          // Normal transition
          expected_rewards(i, j) = FLAGS_normal_reward;
        }


      } else {

        // Cannot move bottom in this condition
        if ((row == cells_per_row - 1) ||
            (grid_world.GetCellState().at(bottom_ind) == -1)) {
          state_transition_tensor(j)(i, i) = 1;
        } else {
          state_transition_tensor(j)(i, bottom_ind) = 1;
        }

        // Setting rewards
        if ((row == cells_per_row - 1) ||
            (grid_world.GetCellState().at(bottom_ind) == -1)) {
          expected_rewards(i, j) = FLAGS_obstacle_reward;
        } else if (grid_world.GetCellState().at(bottom_ind) == 2) {
          // Goal state
          expected_rewards(i, j) = FLAGS_goal_reward;
        } else {
          // Normal transition
          expected_rewards(i, j) = FLAGS_normal_reward;
        }

      }

    }

  }

  std::unique_ptr<FiniteMDP> mdp = std::make_unique<FiniteMDP>(
      state_transition_tensor, num_actions, expected_rewards, 0.1);
  // Test policy where each action has equal probability
  std::unique_ptr<FinitePolicy> policy = std::make_unique<FinitePolicy>(
      MatrixXd::Constant(FLAGS_num_states, num_actions, 0.25));
  PolicyIteration solver(move(mdp), move(policy));

  // Solving for the value function
  solver.Evaluate(0.01);

  // Obtaining the direction of movement from the policy
  VectorXd policy_arrow(FLAGS_num_states);

  for (int i = 0; i < FLAGS_num_states; i++) {

    int ind_policy = 0;

    // Get the position of 1 which is the maximum
    solver.GetPolicyMatrix().row(i).maxCoeff(&ind_policy);
    policy_arrow(i) = ind_policy;

  }

  grid_world.VisualizeValuePolicy(
      solver.GetValueFunctionVector(), policy_arrow);

  return 0;

}



} // namespace examples
} // namespace mnyrve

int main(int argc, char* argv[]) {
  return mnyrve::examples::do_main(argc, argv);
}

#include "environments/grid_world/include/grid_world.h"

namespace mnyrve {
namespace environments {

GridWorld::GridWorld(int num_states, 
                     int num_actions, 
                     double normal_reward, 
                     double obstacle_reward, 
                     double goal_reward):
  num_states_(num_states), num_actions_(num_actions), 
  normal_reward_(normal_reward), obstacle_reward_(obstacle_reward), 
  goal_reward_(goal_reward) {

    MN_REQUIRE((std::sqrt(num_states_) == std::floor(std::sqrt(num_states_))), 
        "The number of states must be a perfect square.");
    cell_state_.reserve(num_states_);

  }

int GridWorld::GetNumStates() {
  return num_states_;
}

int GridWorld::GetNumActions() {
  return num_actions_;
}

double GridWorld::GetNormalReward() {
  return normal_reward_;
}

double GridWorld::GetObstacleReward() {
  return obstacle_reward_;
}

double GridWorld::GetGoalReward() {
  return goal_reward_;
}

std::vector<double> GridWorld::GetCellState() {
  return cell_state_;
}

void GridWorld::SetNumStates(int num_states) {

  MN_REQUIRE((std::sqrt(num_states) == std::floor(std::sqrt(num_states))), 
      "The number of states must be a perfect square.");
  num_states_ = num_states;

}

void GridWorld::SetNumActions(int num_actions) {
  num_actions_ = num_actions;
}

void GridWorld::SetNormalReward(double normal_reward) {
  normal_reward_ = normal_reward;
}

void GridWorld::SetObstacleReward(double obstacle_reward) {
  obstacle_reward_ = obstacle_reward;
}

void GridWorld::SetGoalReward(double goal_reward) {
  goal_reward_ = goal_reward;
}

void GridWorld::SetCellState(std::vector<double> cell_state) {

  MN_REQUIRE((int(cell_state.size()) == num_states_), 
      "The size of the vector must equal the number of states.");
  cell_state_ = cell_state;
}

} // namespace environments
} // namespace mnyrve

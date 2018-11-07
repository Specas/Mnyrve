#ifndef GRID_WORLD_H
#define GRID_WORLD_H

#include "common/include/error_macros.h"

#include "Python.h"
#include <iostream>
#include <fstream>
#include <string>

namespace mnyrve {
namespace environments {

class GridWorld {

  public:
    GridWorld(int num_states,
              int num_actions,
              double normal_reward,
              double obstacle_reward, 
              double goal_reward);

    int GetNumStates();
    int GetNumActions();
    double GetNormalReward();
    double GetObstacleReward();
    double GetGoalReward();
    std::vector<double> GetCellState();
    void SetNumStates(int num_states);
    void SetNumActions(int num_actions);
    void SetNormalReward(double normal_reward);
    void SetObstacleReward(double obstacle_reward);
    void SetGoalReward(double goal_reward);
    void SetCellState(std::vector<double> cell_state);

    void SetUp();



  private:
    int num_states_;
    int num_actions_;
    double normal_reward_;
    double obstacle_reward_;
    double goal_reward_;
    std::vector<double> cell_state_;

};

} // namespace environments 
} // namespace mnyrve

#endif


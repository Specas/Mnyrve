#include "common/include/error_macros.h"
#include "environments/grid_world/include/grid_world.h"

#include <gflags/gflags.h>

namespace mnyrve {
namespace examples {

using mnyrve::environments::GridWorld;

DEFINE_int32(num_states, 36, "Number of cells in the grid");
DEFINE_double(normal_reward, -1, "Reward for taking a normal step");
DEFINE_double(obstacle_reward, -5, "Reward for stepping into an obstacle");
DEFINE_double(goal_reward, 10, "Reward for reaching a goal");

int do_main(int argc, char* argv[]) {

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  // Only considering the four directional actions in this example
  const int num_actions = 4;

  GridWorld grid_world(FLAGS_num_states, 
                       num_actions, 
                       FLAGS_normal_reward, 
                       FLAGS_obstacle_reward, 
                       FLAGS_goal_reward);

  grid_world.SetUp();


  return 0;

}



} // namespace examples
} // namespace mnyrve

int main(int argc, char* argv[]) {
  return mnyrve::examples::do_main(argc, argv);
}

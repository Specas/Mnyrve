#include "gtest/gtest.h"
#include "environments/grid_world/include/grid_world.h"

namespace {

using mnyrve::environments::GridWorld;

class GridWorldTest : public ::testing::Test {

  protected:
    GridWorldTest() {

    }

    void SetUp() override {

    }

    GridWorld gw_1{GridWorld(4, 1, -1, -5, 100)};
    GridWorld gw_2{GridWorld(900, 4, -0.1, -50, 1)};

};

TEST_F(GridWorldTest, InitializationCheck) {

  EXPECT_EQ(gw_1.GetNumStates(), 4);
  EXPECT_EQ(gw_1.GetNumActions(), 1);
  EXPECT_DOUBLE_EQ(gw_1.GetNormalReward(), -1);
  EXPECT_DOUBLE_EQ(gw_1.GetObstacleReward(), -5);
  EXPECT_DOUBLE_EQ(gw_1.GetGoalReward(), 100);

  EXPECT_EQ(gw_2.GetNumStates(), 900);
  EXPECT_EQ(gw_2.GetNumActions(), 4);
  EXPECT_DOUBLE_EQ(gw_2.GetNormalReward(), -0.1);
  EXPECT_DOUBLE_EQ(gw_2.GetObstacleReward(), -50);
  EXPECT_DOUBLE_EQ(gw_2.GetGoalReward(), 1);

  // Error check
  ASSERT_DEATH((GridWorld(901, 4, -0.1, -50, 1)), "");

}

TEST_F(GridWorldTest, SetterCheck) {

  gw_1.SetNumStates(16);
  gw_1.SetNumActions(5);
  gw_1.SetNormalReward(2);
  gw_1.SetObstacleReward(-100);
  gw_1.SetGoalReward(10);

  ASSERT_EQ(gw_1.GetNumStates(), 16);
  ASSERT_EQ(gw_1.GetNumActions(), 5);
  ASSERT_DOUBLE_EQ(gw_1.GetNormalReward(), 2);
  ASSERT_DOUBLE_EQ(gw_1.GetObstacleReward(), -100);
  ASSERT_DOUBLE_EQ(gw_1.GetGoalReward(), 10);

  // Error check
  ASSERT_DEATH((gw_1.SetNumStates(8)), "");

  gw_1.SetNumStates(4);
  std::vector<double> v1 = {1, 2, 3.4, 5.6};
  std::vector<double> v2 = {1, 2, 3.4, 5.6, 7.8};
  gw_1.SetCellState(v1);

  ASSERT_TRUE(gw_1.GetCellState() == v1);

  // Error check
  ASSERT_DEATH((gw_1.SetCellState(v2)), "");


}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



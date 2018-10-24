#include "gtest/gtest.h"
#include "algorithms/include/armed_bandits.h"

using mnyrve::algorithms::ArmedBandits;
using Eigen::MatrixXd;
using Eigen::VectorXd;


namespace {

class ArmedBanditsTest : public ::testing::Test {

  protected:
    ArmedBanditsTest() {


    }

    void SetUp() override {

    }

    ArmedBandits ab1_{ArmedBandits(5, 0.1, 0.1)};
    ArmedBandits ab2_{ArmedBandits(100, 0.5, 0)};

};

TEST_F(ArmedBanditsTest, InitializationCheck) {

  EXPECT_EQ(ab1_.GetK(), 5);
  EXPECT_DOUBLE_EQ(ab1_.GetAlpha(), 0.1);
  EXPECT_DOUBLE_EQ(ab1_.GetEpsilon(), 0.1);
  EXPECT_EQ(ab1_.GetSteps(), 0);
  EXPECT_DOUBLE_EQ(ab1_.GetCumulativeReward(), 0);
  EXPECT_EQ(ab1_.GetActionValue().size(), 5);
  EXPECT_EQ(ab1_.GetActionFrequency().size(), 5);
  EXPECT_TRUE(ab1_.GetActionValue().isZero());
  EXPECT_TRUE(ab1_.GetActionFrequency().isZero());

  EXPECT_EQ(ab2_.GetK(), 100);
  EXPECT_DOUBLE_EQ(ab2_.GetAlpha(), 0.5);
  EXPECT_DOUBLE_EQ(ab2_.GetEpsilon(), 0);
  EXPECT_EQ(ab2_.GetSteps(), 0);
  EXPECT_DOUBLE_EQ(ab2_.GetCumulativeReward(), 0);
  EXPECT_EQ(ab2_.GetActionValue().size(), 100);
  EXPECT_EQ(ab2_.GetActionFrequency().size(), 100);
  EXPECT_TRUE(ab2_.GetActionValue().isZero());
  EXPECT_TRUE(ab2_.GetActionFrequency().isZero());

}

TEST_F(ArmedBanditsTest, SetterCheck) {

  ab1_.SetAlpha(0.9);
  ab1_.SetEpsilon(0.2);
  ASSERT_DOUBLE_EQ(ab1_.GetAlpha(), 0.9); 
  ASSERT_DOUBLE_EQ(ab1_.GetEpsilon(), 0.2); 
  ASSERT_DEATH(ab1_.SetEpsilon(-0.1), ""); 
  ASSERT_DEATH(ab1_.SetEpsilon(1.1), ""); 

  ab2_.SetAlpha(0.8);
  ab2_.SetEpsilon(0.25);
  ASSERT_DOUBLE_EQ(ab2_.GetAlpha(), 0.8); 
  ASSERT_DOUBLE_EQ(ab2_.GetEpsilon(), 0.25); 
  ASSERT_DEATH(ab2_.SetEpsilon(-0.1), ""); 
  ASSERT_DEATH(ab2_.SetEpsilon(1.1), ""); 

}

TEST_F(ArmedBanditsTest, ActionValidityCheck) {

  int action1 = ab1_.TakeAction(); 
  int action2 = ab2_.TakeAction();
  ASSERT_TRUE((action1 >= 0) && (action1 < ab1_.GetK()));
  ASSERT_TRUE((action2 >= 0) && (action2 < ab2_.GetK()));


}

TEST_F(ArmedBanditsTest, RewardCheck1) {

  ASSERT_DEATH((ab1_.RegisterReward(6, 1)), "");
  ab1_.RegisterReward(0, 5);
  ab1_.RegisterReward(4, 10);
  VectorXd res1 = VectorXd::Zero(5);
  res1(0) = 5;
  res1(4) = 10;
  ASSERT_TRUE(ab1_.GetActionValue().isApprox(res1));

  ab2_.RegisterReward(0, 9.5);
  ab2_.RegisterReward(40, 10.1);
  ab2_.RegisterReward(91, 1);
  VectorXd res2 = VectorXd::Zero(100);
  res2(0) = 9.5;
  res2(40) = 10.1;
  res2(91) = 1;
  ASSERT_TRUE(ab2_.GetActionValue().isApprox(res2));

}

TEST_F(ArmedBanditsTest, RewardCheck2) {

  ab1_.RegisterReward(0, 5);
  ab1_.RegisterReward(1, 2);
  ab1_.RegisterReward(4, 3.5);
  ab1_.RegisterReward(0, 5);
  ab1_.RegisterReward(1, 2);
  ab1_.RegisterReward(1, 4);
  VectorXd res1(5);
  res1 << 5, 2.2, 0, 0, 3.5;
  ASSERT_TRUE(ab1_.GetActionValue().isApprox(res1));

  ab2_.RegisterReward(5, 100);
  ab2_.RegisterReward(71, 91);
  ab2_.RegisterReward(5, 101);
  VectorXd res2(100);
  res2(5) = 100.5;
  res2(71) = 91;
  ASSERT_TRUE(ab2_.GetActionValue().isApprox(res2));

}

TEST_F(ArmedBanditsTest, ActionCheck) {


  ab2_.RegisterReward(0, 9.5);
  ab2_.RegisterReward(40, 10.1);
  ab2_.RegisterReward(91, 1);
  ab1_.RegisterReward(2, 4);
  VectorXd res2 = VectorXd::Zero(100);
  res2(0) = 9.5;
  res2(40) = 10.1;
  res2(91) = 1;
  ASSERT_EQ(ab1_.TakeGreedyAction(), 2);
  ASSERT_EQ(ab2_.TakeAction(), 40);
  ASSERT_EQ(ab2_.TakeGreedyAction(), 40);

}


} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

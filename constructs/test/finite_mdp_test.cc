#include "gtest/gtest.h"
#include "constructs/include/finite_mdp.h"

using Eigen::MatrixXd;
using mnyrve::constructs::FiniteMDP;
using mnyrve::math::Tensor3;

namespace {

class FiniteMDPTest : public ::testing::Test {

  protected:
    FiniteMDPTest() {

    t1(0) = MatrixXd::Identity(900, 900);
    t1(1) = MatrixXd::Identity(900, 900);
    t1(2) = MatrixXd::Identity(900, 900);
    t1(3) = MatrixXd::Identity(900, 900);

    t2(0) = MatrixXd::Identity(7, 7);

    }

    void SetUp() override {

    }

    FiniteMDP mdp1_{FiniteMDP(3, 2, 0.1)};

    Tensor3<double> t1{Tensor3<double>(4, 900, 900)};
    MatrixXd m2 = MatrixXd::Random(7, 1);
    Tensor3<double> t2{Tensor3<double>(1, 7, 7)};

};

TEST_F(FiniteMDPTest, InitializationCheck) {

  EXPECT_EQ(mdp1_.GetNumStates(), 3);
  EXPECT_EQ(mdp1_.GetNumActions(), 2);
  EXPECT_EQ(mdp1_.GetGamma(), 0.1);

  FiniteMDP mdp2(t1, 4, 0.01);
  EXPECT_EQ(mdp2.GetNumStates(), 900);
  EXPECT_EQ(mdp2.GetNumActions(), 4);
  EXPECT_EQ(mdp2.GetGamma(), 0.01);

  FiniteMDP mdp3(t2, 1, m2, 0.2);
  EXPECT_EQ(mdp3.GetNumStates(), 7);
  EXPECT_EQ(mdp3.GetNumActions(), 1);
  EXPECT_EQ(mdp3.GetGamma(), 0.2);

  Tensor3<double> t3(2, 30, 30);
  ASSERT_DEATH((FiniteMDP(t3, 2, 1)), "");
  t3(0) = MatrixXd::Identity(30, 30);
  t3(1) = MatrixXd::Identity(30, 30);
  ASSERT_DEATH((FiniteMDP(t3, 3, 1)), "");
  ASSERT_DEATH((FiniteMDP(t3, 2, MatrixXd::Zero(30, 3), 1)), "");
  ASSERT_DEATH((FiniteMDP(t3, 2, MatrixXd::Zero(10, 2), 1)), "");

}

TEST_F(FiniteMDPTest, SetterCheck) {

  mdp1_.SetGamma(0.001);
  ASSERT_EQ(mdp1_.GetGamma(), 0.001);

  Tensor3<double> t4(4, 900, 900);
  FiniteMDP mdp4(t1, 4, 0.01);
  ASSERT_DEATH((mdp4.SetStateTransitionTensor(t4)), "");

  FiniteMDP mdp5(t1, 4, 0.01);
  MatrixXd m3 = MatrixXd::Random(900, 4);
  MatrixXd m4 = MatrixXd::Random(900, 5);
  MatrixXd m5 = MatrixXd::Random(50, 4);
  mdp5.SetExpectedRewards(m3);
  ASSERT_TRUE(mdp5.GetExpectedRewards().isApprox(m3));
  ASSERT_DEATH(mdp5.SetExpectedRewards(m4), "");
  ASSERT_DEATH(mdp5.SetExpectedRewards(m5), "");

}


} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



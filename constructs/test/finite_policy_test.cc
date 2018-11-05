#include "gtest/gtest.h"
#include "constructs/include/finite_policy.h"

namespace {

using Eigen::MatrixXd;
using mnyrve::constructs::FinitePolicy;

class FinitePolicyTest : public ::testing::Test {

  protected:
    FinitePolicyTest() {

    }

    void SetUp() override {

    }

    FinitePolicy fp1_{FinitePolicy(1600, 10)};
    MatrixXd m1 = MatrixXd::Identity(4, 6);
    FinitePolicy fp2_{FinitePolicy(m1)};

};

TEST_F(FinitePolicyTest, InitializationCheck) {

  EXPECT_EQ(fp1_.GetNumStates(), 1600);
  EXPECT_EQ(fp1_.GetNumActions(), 10);
  EXPECT_TRUE(fp1_.GetPolicyMatrix().isZero());

  EXPECT_EQ(fp2_.GetNumStates(), 4);
  EXPECT_EQ(fp2_.GetNumActions(), 6);
  EXPECT_TRUE(fp2_.GetPolicyMatrix().isIdentity());

}

TEST_F(FinitePolicyTest, SetterCheck) {

  MatrixXd m2 = MatrixXd::Random(4, 6);
  fp2_.SetPolicyMatrix(m2);
  ASSERT_TRUE(fp2_.GetPolicyMatrix().isApprox(m2));
  ASSERT_DEATH(fp2_.SetPolicyMatrix(MatrixXd::Zero(4, 5)), "");
  ASSERT_DEATH(fp2_.SetPolicyMatrix(MatrixXd::Zero(2, 6)), "");

}


} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



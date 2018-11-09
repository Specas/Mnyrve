#include "gtest/gtest.h"
#include "algorithms/include/policy_iteration.h"

namespace {

using Eigen::MatrixXd;
using Eigen::VectorXd;
using mnyrve::constructs::FiniteMDP;
using mnyrve::constructs::FinitePolicy;
using mnyrve::constructs::FiniteVFunction;
using mnyrve::algorithms::PolicyIteration;
using mnyrve::math::Tensor3;

class PolicyIterationTest : public ::testing::Test {

  protected:
    PolicyIterationTest() {

      policy_matrix1.block(4, 0, 900 - 4, 1) = MatrixXd::Ones(900 - 4, 1);
      expected_rewards2.resize(2, 3);
      expected_rewards2 << 3, 0, 4, 
                           1, -2, 0;
      m5.resize(2, 2);
      m5 << 0.5, 0.5, 
            1, 0;
      m6.resize(2, 2);
      m6 << 0, 1, 
            0.7, 0.3;
      m7.resize(2, 2);
      m7 << 0.4, 0.6, 
            0.9, 0.1;

      policy_matrix2.resize(2, 3);
      policy_matrix2 << 0.5, 0.5, 0, 
                        0.2, 0, 0.8;

    }

    void SetUp() override {

    }

    MatrixXd expected_rewards1{MatrixXd::Random(900, 4)};
    MatrixXd m1{MatrixXd::Identity(900, 900)};
    MatrixXd m2{MatrixXd::Identity(900, 900)};
    MatrixXd m3{MatrixXd::Identity(900, 900)};
    MatrixXd m4{MatrixXd::Identity(900, 900)};
    MatrixXd policy_matrix1{MatrixXd::Identity(900, 4)};

    MatrixXd expected_rewards2;
    MatrixXd m5, m6, m7;
    MatrixXd policy_matrix2;



};

TEST_F(PolicyIterationTest, InitializationCheck) {

  Tensor3<double> t1({m1, m2, m3, m4});
  PolicyIteration pi1(
      std::make_unique<FiniteMDP>(t1, 4, expected_rewards1, 0.01),
      std::make_unique<FinitePolicy>(policy_matrix1));

  EXPECT_EQ(pi1.GetNumStates(), 900);
  EXPECT_EQ(pi1.GetNumActions(), 4);
  EXPECT_DOUBLE_EQ(pi1.GetGamma(), 0.01);

  pi1.Evaluate(0.01);

  Tensor3<double> t2({m5, m6, m7});
  PolicyIteration pi2(
      std::make_unique<FiniteMDP>(t2, 3, expected_rewards2, 0.2), 
      std::make_unique<FinitePolicy>(policy_matrix2));

  EXPECT_EQ(pi2.GetNumStates(), 2);
  EXPECT_EQ(pi2.GetNumActions(), 3);
  EXPECT_DOUBLE_EQ(pi2.GetGamma(), 0.2);
  
  pi2.Evaluate(1);
  VectorXd value_res(2, 1);
  MatrixXd policy_res(2, 3);
  policy_res << 0, 0, 1, 
                1, 0, 0;

  ASSERT_TRUE(pi2.GetPolicyMatrix().isApprox(policy_res));

}


} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


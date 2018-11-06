#include "gtest/gtest.h"
#include "algorithms/include/iterative_policy_evaluation.h"

namespace {

using Eigen::MatrixXd;
using Eigen::VectorXd;
using mnyrve::algorithms::IterativePolicyEvaluation;
using mnyrve::constructs::FiniteMDP;
using mnyrve::constructs::FinitePolicy;
using mnyrve::constructs::FiniteVFunction;
using mnyrve::math::Tensor3;

class IterativePolicyEvaluationTest : public ::testing::Test {

  protected:
    IterativePolicyEvaluationTest() {

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

TEST_F(IterativePolicyEvaluationTest, InitializationCheck) {

  Tensor3<double> t1({m1, m2, m3, m4});
  IterativePolicyEvaluation ipe1(
      std::make_unique<FiniteMDP>(t1, 4, expected_rewards1, 0.01),
      std::make_unique<FinitePolicy>(policy_matrix1));

  EXPECT_EQ(ipe1.GetNumStates(), 900);
  EXPECT_EQ(ipe1.GetNumActions(), 4);
  EXPECT_DOUBLE_EQ(ipe1.GetGamma(), 0.01);

  ipe1.Evaluate(0.01);

  Tensor3<double> t2({m5, m6, m7});
  IterativePolicyEvaluation ipe2(
      std::make_unique<FiniteMDP>(t2, 3, expected_rewards2, 0.1), 
      std::make_unique<FinitePolicy>(policy_matrix2));

  EXPECT_EQ(ipe2.GetNumStates(), 2);
  EXPECT_EQ(ipe2.GetNumActions(), 3);
  EXPECT_DOUBLE_EQ(ipe2.GetGamma(), 0.1);
  
  ipe2.Evaluate(1);
  VectorXd res(2, 1);
  res << 1.5525, 
         0.3396;
  ASSERT_TRUE(ipe2.GetValue().isApprox(res));


}


} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


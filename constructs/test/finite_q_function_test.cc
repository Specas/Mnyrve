#include "gtest/gtest.h"
#include "constructs/include/finite_q_function.h"

using mnyrve::constructs::FiniteQFunction;
using Eigen::MatrixXd;

namespace {

class FiniteQFunctionTest : public ::testing::Test {

  protected:
    FiniteQFunctionTest() {

    }

    void SetUp() override {

    }

    FiniteQFunction q1_{FiniteQFunction(2, 3)};
    MatrixXd value1 = MatrixXd::Random(73, 101);
    FiniteQFunction q2_{FiniteQFunction(value1)};

};

TEST_F(FiniteQFunctionTest, InitializationCheck) {

  EXPECT_EQ(q1_.GetNumStates(), 2);
  EXPECT_EQ(q1_.GetNumActions(), 3);
  ASSERT_TRUE(q1_.GetValue().isZero());

  EXPECT_EQ(q2_.GetNumStates(), 73);
  EXPECT_EQ(q2_.GetNumActions(), 101);

  for (int i = 0; i < value1.rows(); i++) {
    for (int j = 0; j < value1.cols(); j++) {
      EXPECT_EQ(q2_(i, j), value1(i, j));
    }
  }

}

TEST_F(FiniteQFunctionTest, SetterCheck) {

  MatrixXd value2 = MatrixXd::Random(2, 3);
  MatrixXd value3 = MatrixXd::Random(4, 3);
  MatrixXd value4 = MatrixXd::Random(2, 11);

  q1_.SetValue(value2);
  ASSERT_TRUE(q1_.GetValue().isApprox(value2));

  ASSERT_DEATH(q1_.SetValue(value3), "");
  ASSERT_DEATH(q1_.SetValue(value4), "");

}

TEST_F(FiniteQFunctionTest, OperatorCheck) {

  MatrixXd value5 = MatrixXd::Random(2, 3);
  q1_.SetValue(value5);
  q1_(0, 2) = 0.1;
  q1_(1, 1) = 0.98;
  value5(0, 2) = 0.1;
  value5(1, 1) = 0.98;
  ASSERT_TRUE(q1_.GetValue().isApprox(value5));

}


} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

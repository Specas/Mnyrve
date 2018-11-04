#include "gtest/gtest.h"
#include "constructs/include/finite_v_function.h"

using mnyrve::constructs::FiniteVFunction;
using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace {

class FiniteVFunctionTest : public ::testing::Test {

  protected:
    FiniteVFunctionTest() {

    }

    void SetUp() override {

    }

    FiniteVFunction v1_{FiniteVFunction(5)};
    VectorXd value1 = VectorXd::Random(73);
    FiniteVFunction v2_{FiniteVFunction(value1)};

};

TEST_F(FiniteVFunctionTest, InitializationCheck) {

  EXPECT_EQ(v1_.GetNumStates(), 5);
  ASSERT_TRUE(v1_.GetValue().isZero());
  EXPECT_EQ(v2_.GetNumStates(), 73);
  for (int i = 0; i < value1.rows(); i++) {
    EXPECT_EQ(v2_[i], value1(i));
  }

}

TEST_F(FiniteVFunctionTest, SetterCheck) {
  
  VectorXd value2 = VectorXd::Random(5);
  VectorXd value3 = VectorXd::Random(9);

  v1_.SetValue(value2);
  ASSERT_TRUE(v1_.GetValue().isApprox(value2));

  ASSERT_DEATH((v1_.SetValue(value3)), "");

}

TEST_F(FiniteVFunctionTest, OperatorCheck) {

  VectorXd value2 = VectorXd::Random(5);
  v1_.SetValue(value2);
  v1_[2] = 93.4;
  value2(2) = 93.4;
  ASSERT_TRUE(v1_.GetValue().isApprox(value2));

}

  



} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}





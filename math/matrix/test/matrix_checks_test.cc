#include "gtest/gtest.h"
#include "math/matrix/include/matrix_checks.h"

namespace {

using mnyrve::math::IsSquare;
using mnyrve::math::IsStochasticMatrix;
using Eigen::MatrixXd;

class MatrixChecksTest : public ::testing::Test {

  protected:
    MatrixChecksTest() {

    }

    void SetUp() override {

    }

    MatrixXd m1_{MatrixXd::Random(4, 4)};
    MatrixXd m2_{MatrixXd::Random(2, 3)};
    MatrixXd m3_{MatrixXd::Identity(3, 3)};
    MatrixXd m4_{MatrixXd::Ones(4, 4)};


};

TEST_F(MatrixChecksTest, SquareCheck) {

  ASSERT_TRUE(IsSquare<double>(m1_));
  ASSERT_FALSE(IsSquare<double>(m2_));
  ASSERT_TRUE(IsSquare<double>(m3_));

}

TEST_F(MatrixChecksTest, StochasticCheck) {

  MatrixXd m5(2, 3);
  MatrixXd m6(3, 2);
  m5 << 1, 0, 0,
        0, 0.7, 0.3;
  m6 << 0, 1, 
        0.5, 0.5, 
        2, -1;

  ASSERT_TRUE(IsStochasticMatrix<double>(m3_));
  ASSERT_FALSE(IsStochasticMatrix<double>(m4_));
  ASSERT_TRUE(IsStochasticMatrix<double>(m5));
  ASSERT_FALSE(IsStochasticMatrix<double>(m6));

}




} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

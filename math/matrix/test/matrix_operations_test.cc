#include "gtest/gtest.h"
#include "math/matrix/include/matrix_operations.h"

using Eigen::MatrixXd;
using mnyrve::common::types::MaxMatrixType;
using mnyrve::common::types::MinMatrixType;
using mnyrve::math::MaxOrRandom;
using mnyrve::math::MinOrRandom;

namespace {

class MatrixOperationsTest : public ::testing::Test {

  protected:
    MatrixOperationsTest() {

      m1_.resize(2, 2);
      m2_.resize(3, 2);
      m3_.resize(2, 3);
      m1_ << 0, 1, 
             7.5, 4;
      m2_ << 1, 1, 
             2.5, 9.1, 
             9.1, -4;
      m3_ << 9, -4.5, 1, 
             9, 0, -4.5;

    }

    void SetUp() override {

    }

    MatrixXd m1_;
    MatrixXd m2_;
    MatrixXd m3_;

};

TEST_F(MatrixOperationsTest, MaxMatrixCheck) {

  MaxMatrixType<double> max_matrix_type1 = 
    MaxOrRandom<double>(m1_);
  MaxMatrixType<double> max_matrix_type2 = 
    MaxOrRandom<double>(m2_);
  MaxMatrixType<double> max_matrix_type3 = 
    MaxOrRandom<double>(m3_);

  ASSERT_DOUBLE_EQ(max_matrix_type1.maximum, 7.5);
  ASSERT_EQ(max_matrix_type1.maximum_ind.first, 1);
  ASSERT_EQ(max_matrix_type1.maximum_ind.second, 0);

  ASSERT_DOUBLE_EQ(max_matrix_type2.maximum, 9.1);
  ASSERT_TRUE(((max_matrix_type2.maximum_ind.first == 1) &&
      (max_matrix_type2.maximum_ind.second == 1)) ||
      ((max_matrix_type2.maximum_ind.first == 2) &&
      (max_matrix_type2.maximum_ind.second == 0)));

  ASSERT_DOUBLE_EQ(max_matrix_type3.maximum, 9);
  ASSERT_TRUE(((max_matrix_type3.maximum_ind.first == 0) &&
      (max_matrix_type3.maximum_ind.second == 0)) ||
      ((max_matrix_type3.maximum_ind.first == 1) &&
      (max_matrix_type3.maximum_ind.second == 0)));

}

TEST_F(MatrixOperationsTest, MinMatrixCheck) {

  MinMatrixType<double> min_matrix_type1 = 
    MinOrRandom<double>(m1_);
  MinMatrixType<double> min_matrix_type2 = 
    MinOrRandom<double>(m2_);
  MinMatrixType<double> min_matrix_type3 = 
    MinOrRandom<double>(m3_);

  ASSERT_DOUBLE_EQ(min_matrix_type1.minimum, 0);
  ASSERT_EQ(min_matrix_type1.minimum_ind.first, 0);
  ASSERT_EQ(min_matrix_type1.minimum_ind.second, 0);

  ASSERT_DOUBLE_EQ(min_matrix_type2.minimum, -4);
  ASSERT_EQ(min_matrix_type2.minimum_ind.first, 2);
  ASSERT_EQ(min_matrix_type2.minimum_ind.second, 1);

  ASSERT_DOUBLE_EQ(min_matrix_type3.minimum, -4.5);
  ASSERT_TRUE(((min_matrix_type3.minimum_ind.first == 0) &&
      (min_matrix_type3.minimum_ind.second == 1)) ||
      ((min_matrix_type3.minimum_ind.first == 1) &&
      (min_matrix_type3.minimum_ind.second == 2)));

}



} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

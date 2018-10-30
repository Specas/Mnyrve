#include "gtest/gtest.h"
#include "math/tensor/include/tensor4.h"

using mnyrve::math::Tensor4;
using Eigen::MatrixXd;

namespace {

class Tensor4Test : public ::testing::Test {

  protected:
    Tensor4Test() {

    }

    void SetUp() override {

    }

    Tensor4<double> t1_{Tensor4<double>(2, 2, 2, 2)};
    Tensor4<double> t2_{Tensor4<double>(1, 2, 2, 5)};
    Tensor4<double> t3_{Tensor4<double>(3, 7, 4, 1)};


};

TEST_F(Tensor4Test, InitializationCheck) {

  EXPECT_EQ(t1_.height(), 2);
  EXPECT_EQ(t1_.depth(), 2);
  EXPECT_EQ(t1_.rows(), 2);
  EXPECT_EQ(t1_.cols(), 2);

  EXPECT_EQ(t2_.height(), 1);
  EXPECT_EQ(t2_.depth(), 2);
  EXPECT_EQ(t2_.rows(), 2);
  EXPECT_EQ(t2_.cols(), 5);

  EXPECT_EQ(t3_.height(), 3);
  EXPECT_EQ(t3_.depth(), 7);
  EXPECT_EQ(t3_.rows(), 4);
  EXPECT_EQ(t3_.cols(), 1);

}


TEST_F(Tensor4Test, GetterCheck) {

  ASSERT_TRUE(t1_(1, 0).isApprox(Eigen::MatrixXd::Zero(2, 2))); 
  ASSERT_TRUE(t2_(0, 1).isApprox(Eigen::MatrixXd::Zero(2, 5))); 
  ASSERT_TRUE(t3_(2, 5).isApprox(Eigen::MatrixXd::Zero(4, 1))); 

}

TEST_F(Tensor4Test, SetterCheck1) {

  Eigen::MatrixXd rand_mat1 = Eigen::MatrixXd::Random(2, 2);
  Eigen::MatrixXd rand_mat2 = Eigen::MatrixXd::Random(2, 5);
  Eigen::MatrixXd rand_mat3 = Eigen::MatrixXd::Random(4, 1);

  t1_(0, 0) = rand_mat1;
  t2_(0, 1) = rand_mat2;
  t3_(2, 3) = rand_mat3;

  ASSERT_TRUE(t1_(0, 0).isApprox(rand_mat1));
  ASSERT_TRUE(t1_(1, 0).isApprox(Eigen::MatrixXd::Zero(2, 2)));
  ASSERT_TRUE(t1_(0, 1).isApprox(Eigen::MatrixXd::Zero(2, 2)));

  ASSERT_TRUE(t2_(0, 1).isApprox(rand_mat2));
  ASSERT_TRUE(t2_(0, 0).isApprox(Eigen::MatrixXd::Zero(2, 5)));

  ASSERT_TRUE(t3_(2, 3).isApprox(rand_mat3));
  ASSERT_TRUE(t3_(2, 2).isApprox(Eigen::MatrixXd::Zero(4, 1)));
  ASSERT_TRUE(t3_(2, 4).isApprox(Eigen::MatrixXd::Zero(4, 1)));
  ASSERT_TRUE(t3_(1, 2).isApprox(Eigen::MatrixXd::Zero(4, 1)));
  ASSERT_TRUE(t3_(1, 3).isApprox(Eigen::MatrixXd::Zero(4, 1)));
  ASSERT_TRUE(t3_(1, 4).isApprox(Eigen::MatrixXd::Zero(4, 1)));

}

TEST_F(Tensor4Test, SetterCheck2) {

  t1_(0, 1, 1, 0) = 7;
  t2_(0, 1, 0, 3) = -5;
  t3_(2, 6, 3, 0) = 10;
  
  ASSERT_FALSE(t1_(0, 1).isApprox(Eigen::MatrixXd::Zero(2, 2)));
  ASSERT_FALSE(t2_(0, 1).isApprox(Eigen::MatrixXd::Zero(2, 5)));
  ASSERT_FALSE(t3_(2, 6).isApprox(Eigen::MatrixXd::Zero(4, 1)));

  ASSERT_EQ(t1_(0, 1, 1, 0), 7);
  ASSERT_EQ(t2_(0, 1, 0, 3), -5);
  ASSERT_EQ(t3_(2, 6, 3, 0), 10);

}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



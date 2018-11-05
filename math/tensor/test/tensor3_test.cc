#include "gtest/gtest.h"
#include "math/tensor/include/tensor3.h"

namespace {

using mnyrve::math::Tensor3;
using Eigen::MatrixXd;

class Tensor3Test : public ::testing::Test {

  protected:
    Tensor3Test() {

    }

    void SetUp() override {

    }

    Tensor3<double> t1_{Tensor3<double>(2, 2, 2)};
    Tensor3<double> t2_{Tensor3<double>(1, 2, 2)};
    Tensor3<double> t3_{Tensor3<double>(3, 3, 4)};


};

TEST_F(Tensor3Test, InitializationCheck) {

  EXPECT_EQ(t1_.depth(), 2);
  EXPECT_EQ(t1_.rows(), 2);
  EXPECT_EQ(t1_.cols(), 2);

  EXPECT_EQ(t2_.depth(), 1);
  EXPECT_EQ(t2_.rows(), 2);
  EXPECT_EQ(t2_.cols(), 2);

  EXPECT_EQ(t3_.depth(), 3);
  EXPECT_EQ(t3_.rows(), 3);
  EXPECT_EQ(t3_.cols(), 4);

  // Initializer list initializer check
  MatrixXd m1 = MatrixXd::Random(2, 2);
  MatrixXd m2 = MatrixXd::Random(2, 2);
  MatrixXd m3 = MatrixXd::Random(2, 2);
  Tensor3<double> t4({m1, m2, m3});
  ASSERT_TRUE(t4(0).isApprox(m1));
  ASSERT_TRUE(t4(1).isApprox(m2));
  ASSERT_TRUE(t4(2).isApprox(m3));

}


TEST_F(Tensor3Test, GetterCheck) {

  ASSERT_TRUE(t1_(1).isApprox(Eigen::MatrixXd::Zero(2, 2))); 
  ASSERT_TRUE(t2_(0).isApprox(Eigen::MatrixXd::Zero(2, 2))); 
  ASSERT_TRUE(t3_(2).isApprox(Eigen::MatrixXd::Zero(3, 4))); 

}

TEST_F(Tensor3Test, SetterCheck1) {

  Eigen::MatrixXd rand_mat1 = Eigen::MatrixXd::Random(2, 2);
  Eigen::MatrixXd rand_mat2 = Eigen::MatrixXd::Random(2, 2);
  Eigen::MatrixXd rand_mat3 = Eigen::MatrixXd::Random(3, 4);

  t1_(0) = rand_mat1;
  t2_(0) = rand_mat2;
  t3_(1) = rand_mat3;

  ASSERT_TRUE(t1_(0).isApprox(rand_mat1));
  ASSERT_TRUE(t1_(1).isApprox(Eigen::MatrixXd::Zero(2, 2)));

  ASSERT_TRUE(t2_(0).isApprox(rand_mat2));

  ASSERT_TRUE(t3_(0).isApprox(Eigen::MatrixXd::Zero(3, 4)));
  ASSERT_TRUE(t3_(1).isApprox(rand_mat3));
  ASSERT_TRUE(t3_(2).isApprox(Eigen::MatrixXd::Zero(3, 4)));

}

TEST_F(Tensor3Test, SetterCheck2) {

  t1_(0, 0, 0) = 5;
  t2_(0, 1, 0) = 2;
  t3_(2, 2, 3) = -0.1;

  ASSERT_FALSE(t1_(0).isApprox(Eigen::MatrixXd::Zero(2, 2)));
  ASSERT_FALSE(t2_(0).isApprox(Eigen::MatrixXd::Zero(2, 2)));
  ASSERT_FALSE(t3_(2).isApprox(Eigen::MatrixXd::Zero(3, 4)));

  ASSERT_EQ(t1_(0, 0, 0), 5);
  ASSERT_EQ(t2_(0, 1, 0), 2);
  ASSERT_EQ(t3_(2, 2, 3), -0.1);

}

TEST_F(Tensor3Test, ApproxCheck) {

  Tensor3<double> t5(2, 2, 2); 
  ASSERT_TRUE(t5.isApprox(t1_));
  t5(1) = MatrixXd::Random(2, 2);
  ASSERT_FALSE(t5.isApprox(t1_));

  ASSERT_DEATH((t5.isApprox(Tensor3<double>(1, 2, 2))), "");
  ASSERT_DEATH((t5.isApprox(Tensor3<double>(2, 3, 2))), "");
  ASSERT_DEATH((t5.isApprox(Tensor3<double>(2, 2, 4))), "");

}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

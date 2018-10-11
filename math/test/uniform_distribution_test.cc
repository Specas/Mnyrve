#include "gtest/gtest.h"
#include "math/probability/include/uniform_distribution.h"

using mnyrve::math::UniformDistribution;

namespace {

class UniformDistributionTest : public ::testing::Test {

  protected:
    UniformDistributionTest() {

    }

    void SetUp() override {

    }

    UniformDistribution ud1_{
      UniformDistribution(-10, -5)};

    UniformDistribution ud2_{
      UniformDistribution(-3, 2)};

    UniformDistribution ud3_{
      UniformDistribution(8, 50)};


};

TEST_F(UniformDistributionTest, InitializationCheck) {

  EXPECT_EQ(ud1_.GetA(), -10);
  EXPECT_EQ(ud1_.GetB(), -5);

  EXPECT_EQ(ud2_.GetA(), -3);
  EXPECT_EQ(ud2_.GetB(), 2);

  EXPECT_EQ(ud3_.GetA(), 8);
  EXPECT_EQ(ud3_.GetB(), 50);

  ASSERT_DEATH(
    UniformDistribution ud4_{UniformDistribution(7, 0)}, "");

}

TEST_F(UniformDistributionTest, ComputationCheck1) {

  EXPECT_EQ(ud1_.GetMean(), -7.5);
  EXPECT_DOUBLE_EQ(ud1_.GetVariance(), 25.0/12);

  EXPECT_EQ(ud2_.GetMean(), -0.5);
  EXPECT_DOUBLE_EQ(ud2_.GetVariance(), 25.0/12);

  EXPECT_EQ(ud3_.GetMean(), 29);
  EXPECT_DOUBLE_EQ(ud3_.GetVariance(), 147.0);

}

TEST_F(UniformDistributionTest, ComputationCheck2) {

  EXPECT_DOUBLE_EQ(ud1_.Pdf(-11), 0.0);
  EXPECT_DOUBLE_EQ(ud1_.Pdf(-7), 1.0/5);
  EXPECT_DOUBLE_EQ(ud1_.Cdf(-11), 0.0);
  EXPECT_DOUBLE_EQ(ud1_.Cdf(-8), 2.0/5);
  EXPECT_DOUBLE_EQ(ud1_.Cdf(0), 1.0);

  EXPECT_DOUBLE_EQ(ud2_.Pdf(5), 0.0);
  EXPECT_DOUBLE_EQ(ud2_.Pdf(1), 1.0/5);
  EXPECT_DOUBLE_EQ(ud2_.Cdf(-20), 0.0);
  EXPECT_DOUBLE_EQ(ud2_.Cdf(0), 3.0/5);
  EXPECT_DOUBLE_EQ(ud2_.Cdf(3), 1.0);

  EXPECT_DOUBLE_EQ(ud3_.Pdf(6), 0.0);
  EXPECT_DOUBLE_EQ(ud3_.Pdf(10), 1.0/42);
  EXPECT_DOUBLE_EQ(ud3_.Cdf(5), 0.0);
  EXPECT_DOUBLE_EQ(ud3_.Cdf(12), 4.0/42);
  EXPECT_DOUBLE_EQ(ud3_.Cdf(60), 1.0);

}



} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

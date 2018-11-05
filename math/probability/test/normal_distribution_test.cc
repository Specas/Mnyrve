#include "gtest/gtest.h"
#include "math/probability/include/normal_distribution.h"

namespace {

using mnyrve::math::NormalDistribution;

class NormalDistributionTest : public ::testing::Test {

  protected:
    NormalDistributionTest() {

    }

    void SetUp() override {

    }

    NormalDistribution nd1_{NormalDistribution(4, 10)};
    NormalDistribution nd2_{NormalDistribution(0, 1)};

};

TEST_F(NormalDistributionTest, InitializationCheck) {

  EXPECT_DOUBLE_EQ(nd1_.GetMu(), 4);
  EXPECT_DOUBLE_EQ(nd1_.GetSigma(), 10);

  EXPECT_DOUBLE_EQ(nd2_.GetMu(), 0);
  EXPECT_DOUBLE_EQ(nd2_.GetSigma(), 1);

  ASSERT_DEATH(NormalDistribution nd2_{NormalDistribution(1, 0)}, "");

}

TEST_F(NormalDistributionTest, ComputationCheck1) {

  EXPECT_EQ(nd1_.GetMean(), 4);
  EXPECT_DOUBLE_EQ(nd1_.GetVariance(), 100);
  EXPECT_DOUBLE_EQ(nd1_.GetMaximumPdf(), 0.03989422804014326); 

  EXPECT_EQ(nd2_.GetMean(), 0);
  EXPECT_DOUBLE_EQ(nd2_.GetVariance(), 1);
  EXPECT_DOUBLE_EQ(nd2_.GetMaximumPdf(), 0.39894228040143267); 

}

TEST_F(NormalDistributionTest, ComputationCheck2) {

  EXPECT_DOUBLE_EQ(nd1_.Pdf(2.5), 0.03944793309078889);
  EXPECT_DOUBLE_EQ(nd1_.Pdf(1.2), 0.03836062921534784);
  EXPECT_DOUBLE_EQ(nd1_.Cdf(2.5), 0.4403823076297575);
  EXPECT_DOUBLE_EQ(nd1_.Cdf(1.2), 0.3897387524442028);

  EXPECT_DOUBLE_EQ(nd2_.Pdf(0.5), 0.3520653267642995);
  EXPECT_DOUBLE_EQ(nd2_.Pdf(2), 0.05399096651318807);
  EXPECT_DOUBLE_EQ(nd2_.Cdf(0.5), 0.6914624612740131);
  EXPECT_DOUBLE_EQ(nd2_.Cdf(2), 0.977249868051821);

}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

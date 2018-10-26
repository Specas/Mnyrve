#include "gtest/gtest.h"
#include "math/statistics/include/sampler.h"
#include "math/probability/include/normal_distribution.h"
#include "math/probability/include/uniform_distribution.h"

using mnyrve::math::NormalDistribution;
using mnyrve::math::UniformDistribution;
using mnyrve::math::Sampler;

using Eigen::ArrayXXd;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::ArrayXd;
using std::make_unique;

namespace {

class SamplerTest : public ::testing::Test {

  protected:
    SamplerTest() {

    }

    void SetUp() override {

    }

    Sampler s1_{Sampler(make_unique<UniformDistribution>(-5, 10), -5, 10)};
    Sampler s2_{Sampler(make_unique<NormalDistribution>(0, 1))};

};


TEST_F(SamplerTest, ComputationCheck1) {

  double val1 = s1_.SampleValue();
  Eigen::VectorXd val2 = s1_.SampleVector(5);
  Eigen::MatrixXd val3 = s1_.SampleMatrix(2, 6);

  EXPECT_TRUE(val2.rows() == 5);
  EXPECT_TRUE(val3.rows() == 2);
  EXPECT_TRUE(val3.cols() == 6);

  for (int i = 0; i < 100; i++) {

    ASSERT_TRUE(val1 >= -5);
    ASSERT_TRUE(val1 <= 10);
    ASSERT_TRUE((val2.array()>=ArrayXd::Constant(5, -5)).all());
    ASSERT_TRUE((val2.array()<=ArrayXd::Constant(5, 10)).all());
    ASSERT_TRUE((val3.array()>=ArrayXXd::Constant(2, 6, -5)).all());
    ASSERT_TRUE((val3.array()<=ArrayXXd::Constant(2, 6, 10)).all());
  }

}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



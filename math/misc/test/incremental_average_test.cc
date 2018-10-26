#include "gtest/gtest.h"
#include "math/misc/include/incremental_average.h"

using mnyrve::math::IncrementalAverage;
using mnyrve::common::types::ProcessType;
using Eigen::MatrixXd;

using std::map;


namespace {

class IncrementalAverageTest : public ::testing::Test {

  protected:
    IncrementalAverageTest() {

    }

    void SetUp() override {

    }

    IncrementalAverage<double> ia1_{
      IncrementalAverage<double>(ProcessType::kStationary, 4)};

    IncrementalAverage<double> ia2_{
      IncrementalAverage<double>(
          ProcessType::kStationary, 
          MatrixXd::Ones(4, 1))};

    IncrementalAverage<double> ia3_{
      IncrementalAverage<double>(
          ProcessType::kNonStationary, 
          MatrixXd::Ones(4, 1))};

};

TEST_F(IncrementalAverageTest, InitializationCheck) {

  EXPECT_EQ(ia1_.GetNumVariables(), 4);
  ASSERT_TRUE(ia1_.GetAverages().isZero());
  ASSERT_TRUE(ia1_.GetUpdateCount().isOnes());

  EXPECT_EQ(ia2_.GetNumVariables(), 4);
  ASSERT_TRUE(ia2_.GetAverages().isOnes());
  ASSERT_TRUE(ia2_.GetUpdateCount().isOnes());

  EXPECT_EQ(ia3_.GetNumVariables(), 4);
  ASSERT_TRUE(ia3_.GetAverages().isOnes());
  ASSERT_TRUE(ia3_.GetUpdateCount().isOnes());

}

TEST_F(IncrementalAverageTest, SetterCheck) {

  ASSERT_DEATH(ia1_.SetStepSize(0.1), "");

  ia3_.SetStepSize(0.1);
  ASSERT_TRUE(ia3_.GetUpdateCount().isConstant(0.1));

  ASSERT_DEATH(ia1_.SetAverages(MatrixXd::Random(4, 2)), "");
  ASSERT_DEATH(ia2_.SetAverages(MatrixXd::Random(5, 1)), "");
  ASSERT_DEATH(ia3_.SetAverages(MatrixXd::Random(7, 4)), "");

  MatrixXd observation{MatrixXd::Random(4, 1)};
  ia1_.SetAverages(observation);
  ia2_.SetAverages(observation);
  ia3_.SetAverages(observation);
  ASSERT_TRUE(ia1_.GetAverages().isApprox(observation));
  ASSERT_TRUE(ia2_.GetAverages().isApprox(observation));
  ASSERT_TRUE(ia3_.GetAverages().isApprox(observation));

  observation(1) = 2;
  ia1_.SetAverages(1, 2);
  ia2_.SetAverages(1, 2);
  ia3_.SetAverages(1, 2);
  ASSERT_TRUE(ia1_.GetAverages().isApprox(observation));
  ASSERT_TRUE(ia2_.GetAverages().isApprox(observation));
  ASSERT_TRUE(ia3_.GetAverages().isApprox(observation));

}

TEST_F(IncrementalAverageTest, ComputationCheck1) {

  MatrixXd observation1, observation2, observation3;
  MatrixXd answer1, answer2, answer3;
  observation1.resize(4, 1);
  observation2.resize(4, 1);
  observation3.resize(4, 1);
  answer1.resize(4, 1);
  answer2.resize(4, 1);
  answer3.resize(4, 1);

  observation1 << 1, 1, 2, 2;
  observation2 << 2, -4, 5, 0;
  observation3 << 7, 6, -1, -4;
  answer1 << 2.5, 0.75, 1.5, -0.5;
  answer2 << 2.75, 1, 1.75, -0.25;
  answer3 << 1.69, 1.05, 1.241, 0.491;

  ia1_.Update(observation1);  
  ia1_.Update(observation2);  
  ia1_.Update(observation3);  
  ASSERT_TRUE(ia1_.GetAverages().isApprox(answer1));
  ia2_.Update(observation1);  
  ia2_.Update(observation2);  
  ia2_.Update(observation3);  
  ASSERT_TRUE(ia2_.GetAverages().isApprox(answer2));
  ia3_.SetStepSize(0.1);
  ia3_.Update(observation1);  
  ia3_.Update(observation2);  
  ia3_.Update(observation3);  
  ASSERT_TRUE(ia3_.GetAverages().isApprox(answer3));

}

TEST_F(IncrementalAverageTest, ComputationCheck2) {

  MatrixXd answer1, answer2, answer3;
  answer1.resize(4, 1);
  answer2.resize(4, 1);
  answer3.resize(4, 1);

  answer1 << 0.5, -1, 1.5, 0;
  answer2 << 1, -0.6666666666667, 1.75, 1;
  answer3 << 1, 0.5, 1.241, 1;

  ia1_.Update(0, 1);
  ia1_.Update(1, 1);
  ia1_.Update(1, -4);
  ia1_.Update(2, 2);
  ia1_.Update(2, 5);
  ia1_.Update(2, -1);
  ASSERT_TRUE(ia1_.GetAverages().isApprox(answer1));
  ia2_.Update(0, 1);
  ia2_.Update(1, 1);
  ia2_.Update(1, -4);
  ia2_.Update(2, 2);
  ia2_.Update(2, 5);
  ia2_.Update(2, -1);
  ASSERT_TRUE(ia2_.GetAverages().isApprox(answer2));
  ia3_.SetStepSize(0.1);
  ia3_.Update(0, 1);
  ia3_.Update(1, 1);
  ia3_.Update(1, -4);
  ia3_.Update(2, 2);
  ia3_.Update(2, 5);
  ia3_.Update(2, -1);
  ASSERT_TRUE(ia3_.GetAverages().isApprox(answer3));

}

TEST_F(IncrementalAverageTest, ComputationCheck3) {

  MatrixXd answer1, answer2, answer3;
  answer1.resize(4, 1);
  answer2.resize(4, 1);
  answer3.resize(4, 1);

  answer1 << 0.5, -1, 1.5, 0;
  answer2 << 1, -0.6666666666667, 1.75, 1;
  answer3 << 1, 0.5, 1.241, 1;

  map<double, int> observation_map1, observation_map2, observation_map3;
  observation_map1[0] = 1;
  observation_map1[1] = 1;
  observation_map1[2] = 2;
  observation_map2[1] = -4;
  observation_map2[2] = 5;
  observation_map3[2] = -1;
  
  ia1_.Update(observation_map1);
  ia1_.Update(observation_map2);
  ia1_.Update(observation_map3);
  ASSERT_TRUE(ia1_.GetAverages().isApprox(answer1));
  ia2_.Update(observation_map1);
  ia2_.Update(observation_map2);
  ia2_.Update(observation_map3);
  ASSERT_TRUE(ia2_.GetAverages().isApprox(answer2));
  ia3_.SetStepSize(0.1);
  ia3_.Update(observation_map1);
  ia3_.Update(observation_map2);
  ia3_.Update(observation_map3);
  ASSERT_TRUE(ia3_.GetAverages().isApprox(answer3));

}

} // namespace


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

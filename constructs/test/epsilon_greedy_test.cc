#include "gtest/gtest.h"
#include "constructs/include/epsilon_greedy.h"

using mnyrve::constructs::EpsilonGreedy;

namespace {

class EpsilonGreedyTest : public ::testing::Test {

  protected:
    EpsilonGreedyTest() {

    }

    void SetUp() override {

    }

    EpsilonGreedy eg1_{EpsilonGreedy(0.1)};

};

TEST_F(EpsilonGreedyTest, InitializationCheck) {

  EXPECT_DOUBLE_EQ(eg1_.GetEpsilon(), 0.1);

}

TEST_F(EpsilonGreedyTest, SetterCheck) {

  eg1_.SetEpsilon(0.2);
  EXPECT_DOUBLE_EQ(eg1_.GetEpsilon(), 0.2);

}

TEST_F(EpsilonGreedyTest, OperatorCheck) {

  bool res = eg1_.ActGreedy();

}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}





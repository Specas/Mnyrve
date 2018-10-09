#include "constructs/include/discrete_oracle.h"

namespace mnyrve {
namespace constructs {

DiscreteOracle::DiscreteOracle(int num_rewards) {

  num_rewards_ = num_rewards;
  rewards_ = Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(num_rewards_, 1);
}

DiscreteOracle::DiscreteOracle(
    Eigen::Matrix<double, Eigen::Dynamic, 1> rewards) {
  
  num_rewards_ = rewards.rows();
  rewards_ = rewards;
}

DiscreteOracle::DiscreteOracle(std::map<std::string, double> rewards_map) {

  num_rewards_ = rewards_map.size();
  rewards_.resize(num_rewards_, 1);
  {
    int ind = 0;
    for(auto &elem : rewards_map) {
      rewards_(ind, 0) = elem.second;
      ++ind;
    }
  }
  rewards_map_ = rewards_map;
}

int DiscreteOracle::GetNumRewards() {
  return num_rewards_;
}

Eigen::Matrix<double, Eigen::Dynamic, 1> DiscreteOracle::GetRewards() {
  return rewards_;
}

std::map<std::string, double> DiscreteOracle::GetRewardMap() {
  return rewards_map_;
}

void DiscreteOracle::SetRewards(
    Eigen::Matrix<double, Eigen::Dynamic, 1> rewards) {

  MN_REQUIRE((rewards.size() == num_rewards_), 
      "Reward size should match the initialization size");
  
  rewards_ = rewards;
}
      





} // namespace constructs
} // namespace mnyrve

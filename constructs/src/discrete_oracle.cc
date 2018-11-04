#include "constructs/include/discrete_oracle.h"

namespace mnyrve {
namespace constructs {

DiscreteOracle::DiscreteOracle(int num_rewards) {

  num_rewards_ = num_rewards;
  rewards_ = Eigen::VectorXd::Zero(num_rewards_, 1);
}

DiscreteOracle::DiscreteOracle(Eigen::VectorXd rewards) {
  
  num_rewards_ = rewards.rows();
  rewards_ = rewards;

}

double& DiscreteOracle::operator()(int ind) {
  return rewards_(ind, 0);
}

double& DiscreteOracle::operator()(std::string key) {

  MN_REQUIRE((!rewards_map_.empty()), 
        "Cannot access the oracle by string if a map hasn't been provided.");
  return rewards_map_[key];

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

Eigen::VectorXd DiscreteOracle::GetRewards() {
  return rewards_;
}

std::map<std::string, double> DiscreteOracle::GetRewardMap() {
  return rewards_map_;
}

void DiscreteOracle::SetRewards(
    Eigen::VectorXd rewards) {

  MN_REQUIRE((rewards.size() == num_rewards_), 
      "Reward size should match the initialization size");
  
  rewards_ = rewards;
}

void DiscreteOracle::SetRandomRewards() {

  rewards_ = (Eigen::VectorXd::Random(num_rewards_) +
      Eigen::VectorXd::Ones(num_rewards_))/2.0;

}
      





} // namespace constructs
} // namespace mnyrve

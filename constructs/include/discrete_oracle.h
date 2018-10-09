#ifndef DISCRETE_ORACLE_H
#define DISCRETE_ORACLE_H

#include "common/include/error_macros.h"
#include "third_party/Eigen/Dense"

#include <map>
#include <string>

namespace mnyrve {
namespace constructs {

class DiscreteOracle {

  public:
    DiscreteOracle(int num_rewards);
    DiscreteOracle(Eigen::Matrix<double, Eigen::Dynamic, 1> rewards);
    DiscreteOracle(std::map<std::string, double> rewards_map);

    double& operator[](int ind) {
      return rewards_(ind, 0);
    }

    double& operator[](std::string key) {
      MN_REQUIRE((!rewards_map_.empty()), 
          "Cannot access the oracle by string if a map hasn't been provided.");
      return rewards_map_[key];
    }

    int GetNumRewards();
    Eigen::Matrix<double, Eigen::Dynamic, 1> GetRewards();
    std::map<std::string, double> GetRewardMap();

    void SetRewards(Eigen::Matrix<double, Eigen::Dynamic, 1> rewards);


  private:
    int num_rewards_;
    Eigen::Matrix<double, Eigen::Dynamic, 1> rewards_;
    std::map<std::string, double> rewards_map_;

};



} // namespace constructs
} // namespace mnyrve



#endif

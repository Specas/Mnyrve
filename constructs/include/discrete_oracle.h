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
    DiscreteOracle(Eigen::VectorXd rewards);
    DiscreteOracle(std::map<std::string, double> rewards_map);

    double& operator[](int ind);
    double& operator[](std::string key);

    int GetNumRewards();
    Eigen::VectorXd GetRewards();
    std::map<std::string, double> GetRewardMap();

    void SetRewards(Eigen::VectorXd rewards);

    void SetRandomRewards();

  private:
    int num_rewards_;
    Eigen::VectorXd rewards_;
    std::map<std::string, double> rewards_map_;

};



} // namespace constructs
} // namespace mnyrve



#endif

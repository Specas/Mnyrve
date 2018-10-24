#ifndef ARMED_BANDITS_H
#define ARMED_BANDITS_H

#include "common/include/error_macros.h"
#include "common/include/types.h"
#include "constructs/include/epsilon_greedy.h"
#include "math/matrix/include/matrix_operations.h"
#include "math/misc/include/incremental_average.h"
#include "third_party/Eigen/Dense"

namespace mnyrve {
namespace algorithms {

class ArmedBandits {

  public: 
    ArmedBandits(int k, double alpha, double epsilon);
    int GetK();
    double GetAlpha();
    double GetEpsilon();
    int GetSteps();
    double GetCumulativeReward();
    Eigen::VectorXd GetActionValue();
    Eigen::Matrix<int, Eigen::Dynamic, 1> GetActionFrequency();
    void SetAlpha(double alpha);
    void SetEpsilon(double epsilon);

    int TakeAction();
    int TakeGreedyAction();
    void RegisterReward(int ind, double reward);


  private:
    int k_;
    double alpha_;
    double epsilon_;
    int steps_;
    double cumulative_reward_;
    Eigen::Matrix<int, Eigen::Dynamic, 1> action_frequency_;
    mnyrve::math::IncrementalAverage<double> average_manager_;
    mnyrve::constructs::EpsilonGreedy epsilon_greedy_;

};

} // namespace algorithms 
} // namespace mnyrve

#endif


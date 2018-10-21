#ifndef ARMED_BANDITS_H
#define ARMED_BANDITS_H

#include "common/include/error_macros.h"
#include "common/include/types.h"
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
    double GetCumulativeReward();
    Eigen::VectorXd GetActionValue();
    Eigen::VectorXd GetActionFrequency();
    void SetAlpha(double alpha);
    void SetEpsilon(double epsilon);

    int TakeAction();


  private:
    int k_;
    double alpha_;
    double epsilon_;
    Eigen::VectorXd action_value_;
    Eigen::VectorXd action_frequency_;
    double cumulative_reward_;
    mnyrve::math::IncrementalAverage<double> average_manager_;

};

} // namespace algorithms 
} // namespace mnyrve

#endif


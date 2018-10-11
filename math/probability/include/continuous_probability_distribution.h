#ifndef CONTINUOUS_PROBABILITY_DISTRIBUTION_H
#define CONTINUOUS_PROBABILITY_DISTRIBUTION_H

#include "common/include/error_macros.h"

namespace mnyrve {
namespace math {

class ContinuousProbabilityDistribution {

  public:
    virtual ~ContinuousProbabilityDistribution() = 0;
    double GetMean();
    double GetVariance();
    void SetMean(double mean);
    void SetVariance(double variance);


  private:
    double mean_;
    double variance_;

};


} // namespace math
} // namespace mnyrve


#endif

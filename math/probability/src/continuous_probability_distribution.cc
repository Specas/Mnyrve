#include "math/probability/include/continuous_probability_distribution.h"

namespace mnyrve{
namespace math{

ContinuousProbabilityDistribution::~ContinuousProbabilityDistribution(){}

double ContinuousProbabilityDistribution::GetMean() {
  return mean_;
}

double ContinuousProbabilityDistribution::GetVariance() {
  return variance_;
}

void ContinuousProbabilityDistribution::SetMean(double mean) {
  mean_ = mean;
}

void ContinuousProbabilityDistribution::SetVariance(double variance) {
  variance_ = variance;
}


} // namespace math
} // namespace mnyrve

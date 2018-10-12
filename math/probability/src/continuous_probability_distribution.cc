#include "math/probability/include/continuous_probability_distribution.h"

namespace mnyrve{
namespace math{

ContinuousProbabilityDistribution::ContinuousProbabilityDistribution(
    double mean, double variance, double maximum_pdf) :
  mean_(mean), variance_(variance), maximum_pdf_(maximum_pdf) {}

ContinuousProbabilityDistribution::~ContinuousProbabilityDistribution(){}

double ContinuousProbabilityDistribution::GetMean() {
  return mean_;
}

double ContinuousProbabilityDistribution::GetVariance() {
  return variance_;
}

double ContinuousProbabilityDistribution::GetMaximumPdf() {
  return maximum_pdf_;
}

double Pdf(double x) {
  return 0;
}

double Cdf(double x) {
  return 0;
}


} // namespace math
} // namespace mnyrve

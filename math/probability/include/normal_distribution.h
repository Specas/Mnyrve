#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

#include "math/probability/include/continuous_probability_distribution.h"

#include <cmath>

namespace mnyrve {
namespace math {

class NormalDistribution : public ContinuousProbabilityDistribution {

  public:
    NormalDistribution(double mu, double sigma);
    ~NormalDistribution();
    double GetMu();
    double GetSigma();

    double Pdf(double x) const override;
    double Cdf(double x) const override;

  private:
    double mu_;
    double sigma_;
};


} // namespace math
} // namespace mnyrve

#endif

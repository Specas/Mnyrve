#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include "math/probability/include/continuous_probability_distribution.h"

#include <cmath>

namespace mnyrve {
namespace math {

class UniformDistribution : public ContinuousProbabilityDistribution {

  public:
    UniformDistribution(double a, double b);
    ~UniformDistribution();
    double GetA();
    double GetB();

    double Pdf(double x) const override;
    double Cdf(double x) const override;

  private:
    double a_;
    double b_;

};

} // namespace math
} // namespace mnyrve

#endif

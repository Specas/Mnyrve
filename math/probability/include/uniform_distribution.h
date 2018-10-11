#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include "common/include/error_macros.h"
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

    double Pdf(double x);
    double Cdf(double x);

  private:
    double a_;
    double b_;

};


} // namespace math
} // namespace mnyrve

#endif

#ifndef CONTINUOUS_PROBABILITY_DISTRIBUTION_H
#define CONTINUOUS_PROBABILITY_DISTRIBUTION_H

#include "common/include/error_macros.h"

namespace mnyrve {
namespace math {

class ContinuousProbabilityDistribution {

  public:
    ContinuousProbabilityDistribution(double mean,
                                      double variance,
                                      double maximum_pdf);
    virtual ~ContinuousProbabilityDistribution() = 0;

    double GetMean();
    double GetVariance();
    double GetMaximumPdf();

    virtual double Pdf(double x) const = 0;
    virtual double Cdf(double x) const = 0;

  private:
    double mean_;
    double variance_;
    double maximum_pdf_;

};


} // namespace math
} // namespace mnyrve


#endif

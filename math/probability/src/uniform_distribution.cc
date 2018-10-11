#include "math/probability/include/uniform_distribution.h"

namespace mnyrve {
namespace math { 

UniformDistribution::~UniformDistribution() {}

UniformDistribution::UniformDistribution(double a, double b) :
  ContinuousProbabilityDistribution(
      0.5*(a + b), (1.0/12)*std::pow((b - a), 2)) {

    MN_REQUIRE((a<=b), 
        "a has to be lesser than b.");
    a_ = a;
    b_ = b;

}

double UniformDistribution::GetA() {
  return a_;
}

double UniformDistribution::GetB() {
  return b_;
}

double UniformDistribution::Pdf(double x) const {

  double pdf_val = 0;
  if (x >= a_ && x <= b_) {
    pdf_val = 1.0/(b_ - a_);
  }
  return pdf_val;

}

double UniformDistribution::Cdf(double x) const {

  double cdf_val = 0;
  if (x >= a_ && x < b_) {
    cdf_val = (x - a_)/(b_ - a_);
  }
  if (x >= b_) {
    cdf_val = 1;
  }
  return cdf_val;

}

} // namespace math
} // namespace mnyrve

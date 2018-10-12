#include "math/probability/include/normal_distribution.h"

namespace mnyrve {
namespace math { 

NormalDistribution::~NormalDistribution() {}

NormalDistribution::NormalDistribution(double mu, double sigma) :
  ContinuousProbabilityDistribution(mu,
                                    std::pow(sigma, 2),
                                    1.0/std::sqrt(2*M_PI*std::pow(sigma_, 2))) {

  MN_REQUIRE((sigma!=0), "Sigma cannot be zero.");
  mu_ = mu;
  sigma_ = sigma;

}

double NormalDistribution::GetMu() {
  return mu_;
}

double NormalDistribution::GetSigma() {
  return sigma_;
}

double NormalDistribution::Pdf(double x) const {

  return (1.0/std::sqrt(2*M_PI*std::pow(sigma_, 2)))*
    std::exp(-std::pow(x - mu_, 2)/(2*std::pow(sigma_, 2)));

}

double NormalDistribution::Cdf(double x) const {

  return 0.5*(1 + std::erf((x - mu_)/(std::sqrt(2)*sigma_)));

}

} // namespace math
} // namespace mnyrve

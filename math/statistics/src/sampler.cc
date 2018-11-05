#include "math/statistics/include/sampler.h"

namespace mnyrve {
namespace math {

using ContDistribution = mnyrve::math::ContinuousProbabilityDistribution;

Sampler::Sampler(std::unique_ptr<ContDistribution> distribution, 
                 double x_min, 
                 double x_max) :
  distribution_(std::move(distribution)), x_min_(x_min), x_max_(x_max) {}

double Sampler::SampleValue() {

  std::random_device rd;
  std::mt19937 generator(rd()); 
  double sample;

  bool done{false};
  while (!done) {
    std::uniform_real_distribution<> initial_sample(x_min_, x_max_);
    std::uniform_real_distribution<> rejection_sample(0, 
        distribution_->GetMaximumPdf());
    sample = initial_sample(generator);
    if (distribution_->Pdf(sample) > rejection_sample(generator)) {
      done = true;
    }
  }

  return sample;

}

Eigen::VectorXd Sampler::SampleVector(int num_variables) {

  Eigen::VectorXd sample(num_variables);
  for (int i = 0; i < num_variables; i++) {
    sample(i) = this->SampleValue();
  }

  return sample;

}

Eigen::MatrixXd Sampler::SampleMatrix(int num_rows, int num_cols) {

  Eigen::MatrixXd sample(num_rows, num_cols);
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      sample(i, j) = this->SampleValue();
    }
  }

  return sample;

}

} // namespace math
} // namespace mnyrve



#ifndef SAMPLER_H
#define SAMPLER_H

#include "math/probability/include/continuous_probability_distribution.h"
#include "third_party/Eigen/Dense"

#include <memory>
#include <random>

namespace mnyrve {
namespace math {

class Sampler {

  public:
    Sampler(std::unique_ptr
        <ContinuousProbabilityDistribution> distribution, 
        double x_min = -std::numeric_limits<double>::infinity(),
        double x_max = std::numeric_limits<double>::infinity());

    double SampleValue();
    Eigen::VectorXd SampleVector(int num_variables);
    Eigen::MatrixXd SampleMatrix(int num_rows, int num_cols);

  private:
    std::unique_ptr<ContinuousProbabilityDistribution> distribution_;
    double x_min_;
    double x_max_;

};

} // namespace math
} // namespace mnyrve


#endif

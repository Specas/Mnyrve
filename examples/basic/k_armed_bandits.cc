#include "algorithms/include/armed_bandits.h"
#include "constructs/include/discrete_oracle.h"
#include "math/probability/include/normal_distribution.h"
#include "math/statistics/include/sampler.h"

#include "third_party/Eigen/Dense"
#include <gflags/gflags.h>

namespace mnyrve {
namespace examples {

using mnyrve::algorithms::ArmedBandits;
using mnyrve::constructs::DiscreteOracle;
using mnyrve::math::NormalDistribution;
using mnyrve::math::Sampler;
using Eigen::VectorXd;

DEFINE_int32(k, 10, "Number of actions in the bandit problem");
DEFINE_double(alpha, 0.1, "Averaging step size");
DEFINE_double(epsilon, 0.1, "Averaging step size");

int main(int argc, char* argv[]) {


  gflags::ParseCommandLineFlags(&argc, &argv, true);

  ArmedBandits armed_bandit(FLAGS_k, FLAGS_alpha, FLAGS_epsilon);
  Sampler sampler(std::make_unique<NormalDistribution>
      (1.0, 1.0), 0.5, 1.5);
  Sampler noise_sampler(std::make_unique<NormalDistribution>
      (0.0, 1.0), -1.0, 1.0);
  VectorXd average_rewards = sampler.SampleVector(FLAGS_k);
  DiscreteOracle oracle(average_rewards);

  int max_iterations{100000};

  for (int i = 0; i< max_iterations; i++) {

    int action = armed_bandit.TakeAction();
    double reward = oracle[action] + noise_sampler.SampleValue();
    armed_bandit.RegisterReward(action, reward);

  }


  return 0;

}


} // namespace examples
} // namespace mnyrve

int main(int argc, char* argv[]) {
  return mnyrve::examples::main(argc, argv);
}

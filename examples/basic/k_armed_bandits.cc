#include "algorithms/include/armed_bandits.h"
#include "common/include/types.h"
#include "constructs/include/discrete_oracle.h"
#include "math/probability/include/normal_distribution.h"
#include "math/statistics/include/sampler.h"
#include "third_party/Eigen/Dense"
#include "visualization/include/plot2d.h"

#include <gflags/gflags.h>

namespace mnyrve {
namespace examples {

using mnyrve::algorithms::ArmedBandits;
using mnyrve::common::types::PlotDetails;
using mnyrve::common::types::Limits;
using mnyrve::constructs::DiscreteOracle;
using mnyrve::math::NormalDistribution;
using mnyrve::math::Sampler;
using mnyrve::visualization::Plot2d;
using Eigen::VectorXd;

DEFINE_int32(k, 10, "Number of actions in the bandit problem");
DEFINE_double(alpha, 0.1, "Averaging step size");
DEFINE_double(epsilon, 0.01, "Averaging step size");

int main(int argc, char* argv[]) {

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  const double reward_mean = 1.0;
  const double reward_std = 1.0;
  const double reward_lower = 0.0;
  const double reward_upper = 2.0;
  const double noise_mean = 0.0;
  const double noise_std = 1.0;
  const double noise_lower = -0.1;
  const double noise_upper = 0.1;

  ArmedBandits armed_bandit(FLAGS_k, FLAGS_alpha, FLAGS_epsilon);
  Sampler sampler(std::make_unique<NormalDistribution>
      (reward_mean, reward_std), reward_lower, reward_upper);
  Sampler noise_sampler(std::make_unique<NormalDistribution>
      (noise_mean, noise_std), noise_lower, noise_upper);
  VectorXd average_rewards = sampler.SampleVector(FLAGS_k);
  DiscreteOracle oracle(average_rewards);

  int max_iterations{1000};
  VectorXd x_iter = VectorXd::LinSpaced(1000, 1, 1000);
  VectorXd y_reward(1000);

  for (int i = 0; i< max_iterations; i++) {

    int action = armed_bandit.TakeAction();
    double reward = oracle[action] + noise_sampler.SampleValue();
    armed_bandit.RegisterReward(action, reward);

    y_reward(i) = reward;

  }

  // Plotting
  Plot2d plotter;
  PlotDetails plot_details = {};
  Limits x_limits = {};
  Limits y_limits = {};
  x_limits.lower = 0;
  x_limits.upper = max_iterations;
  y_limits.lower = 0;
  y_limits.upper = reward_upper + noise_upper;
  plot_details.figure_title = "k-Armed Bandits Evaluation";
  plot_details.plot_title = "Reward vs Iterations";
  plot_details.x_label = "Iterations";
  plot_details.y_label = "Rewards";
  plot_details.fmt = 'b';
  plot_details.x_limits = x_limits;
  plot_details.y_limits = y_limits;
  plotter.PlotComplete(x_iter, y_reward, plot_details);

  return 0;

}


} // namespace examples
} // namespace mnyrve

int main(int argc, char* argv[]) {
  return mnyrve::examples::main(argc, argv);
}

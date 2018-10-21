#ifndef EPSILON_GREEDY_H
#define EPSILON_GREEDY_H

#include "common/include/error_macros.h"
#include "math/probability/include/uniform_distribution.h"
#include "math/statistics/include/sampler.h"

namespace mnyrve {
namespace constructs {

class EpsilonGreedy {

  public:
    EpsilonGreedy(double epsilon);
    double GetEpsilon();
    void SetEpsilon(double epsilon);

    bool ActGreedy();

  private:
    double epsilon_;
    mnyrve::math::Sampler sampler_;

};

} // namespace constructs
} // namespace mnyrve 

#endif


#ifndef VALUE_ITERATION
#define VALUE_ITERATION

#include "constructs/include/finite_mdp.h"
#include "constructs/include/finite_policy.h"
#include "constructs/include/finite_v_function.h"
#include "third_party/Eigen/Dense"

#include <memory>

namespace mnyrve {
namespace algorithms {

class ValueIteration {

  public:
    ValueIteration(
        std::unique_ptr<mnyrve::constructs::FiniteMDP> mdp, 
        std::unique_ptr<mnyrve::constructs::FinitePolicy> init_policy);

    int GetNumStates();
    int GetNumActions();
    double GetGamma();
    Eigen::VectorXd GetValueFunctionVector();
    mnyrve::constructs::FiniteVFunction GetValueFunction();
    Eigen::MatrixXd GetPolicyMatrix();
    mnyrve::constructs::FinitePolicy GetPolicy();

    void Evaluate(double stop_threshold);

  private:
    std::unique_ptr<mnyrve::constructs::FiniteMDP> mdp_;
    std::unique_ptr<mnyrve::constructs::FinitePolicy> policy_;
    mnyrve::constructs::FiniteVFunction v_function_;
    int num_states_;
    int num_actions_;
    double gamma_;

};



} // namespace algorithms
} // namespace mnyrve

#endif

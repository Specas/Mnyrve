#ifndef INCREMENTAL_AVERAGE_H
#define INCREMENTAL_AVERAGE_H

#include "common/include/error_macros.h"
#include "common/include/types.h"
#include "third_party/Eigen/Dense"

#include <map>

namespace mnyrve {
namespace math {

template<typename T>
class IncrementalAverage {

  public:
    IncrementalAverage(
        mnyrve::common::types::ProcessType process_type,
        int num_variables) {

      process_type_ = process_type;
      num_variables_ = num_variables;
      averages_ = Eigen::VectorXd::Zero(
          num_variables_, 1);
      update_count_ = Eigen::VectorXd::Ones(
          num_variables_, 1);

    }

    IncrementalAverage(
        mnyrve::common::types::ProcessType process_type,
        Eigen::VectorXd averages) {

      process_type_ = process_type;
      num_variables_ = averages.rows();
      averages_ = averages;
      update_count_ = Eigen::VectorXd::Ones(
          num_variables_, 1);

    }

    void Update(Eigen::VectorXd observation) {

      MN_REQUIRE((observation.rows() == num_variables_),
          "Observation size should equal the initialized variable size.");

      if(process_type_ == mnyrve::common::types::ProcessType::kStationary) {

        update_count_ = update_count_ + 
          Eigen::VectorXd::Ones(num_variables_, 1);
        Eigen::VectorXd residue = 
          (observation.array() - averages_.array())/update_count_.array();
        averages_ = averages_ + residue;

      } else {

        Eigen::VectorXd residue = 
          (observation.array() - averages_.array())*update_count_.array();
        averages_ = averages_ + residue;
      }
    }

    void Update(int index, T single_observation) {

      if(process_type_ == mnyrve::common::types::ProcessType::kStationary) {

        update_count_(index, 0) = update_count_(index, 0) + 1;
        averages_(index, 0) = averages_(index, 0) +
          (single_observation - averages_(index, 0))/update_count_(index, 0);

      } else {

        averages_(index, 0) = averages_(index, 0) +
          (single_observation - averages_(index, 0))*update_count_(index, 0);
      }
    }

    void Update(std::map<T, int> observation_map) {

        for(auto const& elem : observation_map) {
          Update(elem.first, elem.second);
        }

    }

    void SetStepSize(double step_size) {

      MN_REQUIRE(
          (process_type_ == mnyrve::common::types::ProcessType::kNonStationary), 
          "Trying to set a constant step size to track a stationary process.");

      update_count_ =
        Eigen::VectorXd::Constant(
            num_variables_, 1, step_size);

    }

    void SetAverages(Eigen::VectorXd averages) {

      MN_REQUIRE(
          (averages.size() == num_variables_), 
          "The averages must be of the same initialized variable size.");

      averages_ = averages;

    }

    Eigen::VectorXd GetAverages() {

     return averages_;

    }

    int GetNumVariables() {

      return num_variables_;

    }

    Eigen::VectorXd GetUpdateCount() {

      return update_count_;

    }


  private:
    mnyrve::common::types::ProcessType process_type_;
    int num_variables_;
    Eigen::VectorXd averages_;
    Eigen::VectorXd update_count_;


};


} // math
} // mnyrve


#endif

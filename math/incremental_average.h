#ifndef INCREMENTAL_AVERAGE_H
#define INCREMENTAL_AVERAGE_H

#include "common/error_macros.h"
#include "common/types.h"
#include "third_party/Eigen/Dense"

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
      averages_ = Eigen::Matrix<T, Eigen::Dynamic, 1>::Zeros(
          num_variables_, 1);
      update_count_ = Eigen::Matrix<int, Eigen::Dynamic, 1>::Ones(
          num_variables_, 1);

    }

    IncrementalAverage(
        mnyrve::common::types::ProcessType process_type,
        Eigen::Matrix<T, Eigen::Dynamic, 1> averages) {

      process_type_ = process_type;
      num_variables_ = averages.rows();
      averages_ = averages;
      update_count_ = Eigen::Matrix<int, Eigen::Dynamic, 1>::Ones(
          num_variables_, 1);

    }


  private:
    mnyrve::common::types::ProcessType process_type_;
    int num_variables_;
    Eigen::Matrix<T, Eigen::Dynamic, 1> averages_;
    Eigen::Matrix<int, Eigen::Dynamic, 1> update_count_;

};


} // math
} // mnyrve


#endif

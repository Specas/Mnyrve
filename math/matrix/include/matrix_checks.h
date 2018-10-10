#ifndef MATRIX_CHECKS_H
#define MATRIX_CHECKS_H

#include "common/include/types.h"
#include "third_party/Eigen/Dense"

namespace mnyrve {
namespace math {

template<typename T>
bool IsSquare(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> m) {
  return m.rows() == m.cols();
}

template<typename T>
bool IsStochasticMatrix(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> m) {
  auto col_sum = m.rowwise().sum();
  return col_sum.isOnes();
}

} // math
} // mnyrve


#endif

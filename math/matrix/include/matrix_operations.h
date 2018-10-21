#ifndef MATRIX_CHECKS_H
#define MATRIX_CHECKS_H

#include "common/include/types.h"
#include "third_party/Eigen/Dense"

#include <random>

namespace mnyrve {
namespace math {

template<typename T>
mnyrve::common::types::MaxMatrixType<double> MaxOrRandom(
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> m) {

  T maximum = m.maxCoeff();
  std::pair<int, int> maximum_ind(0, 0);
  std::vector<std::pair<int, int>> maximum_indices;

  for (int i = 0; i < m.rows(); i++) {
    for (int j = 0; j < m.cols(); j++) {

      if (m(i, j) == maximum) {

        maximum_indices.emplace_back(i, j);

      }

    }
  }

  // Selecting a random maximum from the equal ones
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> ud(0, maximum_indices.size() - 1);


  mnyrve::common::types::MaxMatrixType<double> max_matrix_type = 
    {maximum, maximum_indices.at(ud(generator))};

  return max_matrix_type; 

}


template<typename T>
mnyrve::common::types::MinMatrixType<double> MinOrRandom(
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> m) {

  T minimum = m.minCoeff();
  std::pair<int, int> minimum_in(0, 0);
  std::vector<std::pair<int, int>> minimum_indices;

  for (int i = 0; i < m.rows(); i++) {
    for (int j = 0; j < m.cols(); j++) {

      if (m(i, j) == minimum) {

        minimum_indices.emplace_back(i, j);

      }

    }
  }

  // Selecting a random maximum from the equal ones
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> ud(0, minimum_indices.size() - 1);

  mnyrve::common::types::MinMatrixType<double> min_matrix_type = 
    {minimum, minimum_indices.at(ud(generator))};

  return min_matrix_type; 

}


} // namespace math
} // namespace mnyrve




#endif

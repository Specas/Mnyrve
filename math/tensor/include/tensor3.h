#ifndef TENSOR3_H
#define TENSOR3_H

#include "common/include/error_macros.h"
#include "third_party/Eigen/Dense"

namespace mnyrve {
namespace math {

template<typename type>
class Tensor3 {

  public:
    Tensor3(int depth, int rows, int cols) {

      depth_ = depth;
      rows_ = rows;
      cols_ = cols;
      actual_rows_ = rows;
      actual_cols_ = cols*depth;
      m_.resize(actual_rows_, actual_cols_);
      SetM(Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic>
          ::Zero(actual_rows_, actual_cols_));

    }

    int depth() {
      return depth_;
    }

    int rows() {
      return rows_;
    }

    int cols() {
      return cols_;
    }


    void SetZero() {

      SetM(Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic>
        ::Zero(actual_rows_, actual_cols_));

    }

    Eigen::Ref<Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic>> operator()(
        int depth_index) {

      return m_.block(0, depth_index*cols_, actual_rows_, cols_);

    }

    type& operator()(int depth_index, int row_index, int column_index) {

      return m_(row_index, depth_index*cols_ + column_index);

    }

  private:
    int depth_;
    int rows_;
    int cols_;
    int actual_rows_;
    int actual_cols_;
    Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> m_;

    void SetM(Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> m) {
      m_ = m;
    }


};


} // namespace math
} // namespace mnyrve

#endif
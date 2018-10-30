#ifndef TENSOR4_H
#define TENSOR4_H

#include "common/include/error_macros.h"
#include "third_party/Eigen/Dense"

namespace mnyrve {
namespace math {

template<typename type>
class Tensor4 {

  public:
    Tensor4(int height, int depth, int rows, int cols) {

      height_ = height;
      depth_ = depth;
      rows_ = rows;
      cols_ = cols;
      actual_rows_ = rows*height;
      actual_cols_ = cols*depth;
      SetM(Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic>
          ::Zero(actual_rows_, actual_cols_));

    }

    int height() {
      return height_;
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
        int height_index, int depth_index) {

      return m_.block(height_index*rows_, depth_index*cols_, rows_, cols_);

    }

    type& operator()(
        int height_index, int depth_index, int row_index, int column_index) {

      return m_(height_index*rows_ + row_index,
          depth_index*cols_ + column_index);

    }

  private:
    int height_;
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


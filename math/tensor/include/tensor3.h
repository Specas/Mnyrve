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

    Tensor3(std::initializer_list<Eigen::Matrix<type,
        Eigen::Dynamic, Eigen::Dynamic>> list) {

      depth_ = list.size();
      rows_ = (*list.begin()).rows();
      cols_ = (*list.begin()).cols();
      actual_rows_ = rows_;
      actual_cols_ = cols_*depth_;
      m_.resize(actual_rows_, actual_cols_);
      for (int i = 0; i < depth_; i++) {
        this->operator()(i) = *(list.begin() + i);
      }

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

    bool isApprox(Tensor3<type> tensor) {

      MN_REQUIRE(((this->depth() == tensor.depth()) &&
            (this->rows() == tensor.rows()) &&
            (this->cols() == tensor.cols())), 
          "Tensor dimensions must match.");

      bool res{true};
      for (int i = 0; i < tensor.depth(); i++) {
        res = res && (this->operator()(i).isApprox(tensor(i)));
      }

      return res;

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

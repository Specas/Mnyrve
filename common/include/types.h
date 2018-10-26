#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include <string>

namespace mnyrve {
namespace common {
namespace types {

enum class DomainType {

  kDiscrete = 0, 
  kContinuous = 1,

};

enum class MatrixAxisType {

  kRow = 0, 
  kCol = 1,

};

enum class ProcessType {

  kStationary = 0,
  kNonStationary = 1,

};

enum class DistributionType {

  kUniform = 0,
  kNormal = 0,

};

template <typename T>
struct MaxMatrixType {

  T maximum;
  std::pair<int, int> maximum_ind;

};


template <typename T>
struct MinMatrixType {

  T minimum;
  std::pair<int, int> minimum_ind;

};

struct Limits {

  double lower;
  double upper;

};

struct PlotDetails {

  std::string figure_title;
  std::string plot_title;
  std::string x_label;
  std::string y_label;
  std::string fmt;

  Limits x_limits;
  Limits y_limits;

};



} // namespace types
} // namespace common
} // namespace mnyrve

#endif


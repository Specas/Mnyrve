#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

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



} // namespace types
} // namespace common
} // namespace mnyrve

#endif


#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H
//#pragma once

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

} // namespace types
} // namespace common
} // namespace mnyrve

#endif


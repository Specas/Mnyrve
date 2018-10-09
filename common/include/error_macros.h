#ifndef ERROR_MACROS_H
#define ERROR_MACROS_H

#include "third_party/Eigen/Dense"

#include <iostream>

namespace mnyrve {
namespace common {
namespace macros {

#ifndef NDEBUG
  #define MN_ASSERT(condition, error_message) {\
    if(!condition) {\
      std::cerr << "----------Assertion Failed----------" << std::endl;\
      std::cerr << "Assertion failed in file: " << __FILE__ << std::endl;\
      std::cerr << "Assertion failed at line: " << __LINE__ << std::endl;\
      std::cerr << "Assertion failed inside function: " <<\
        __FUNCTION__ << std::endl;\
      std::cerr << "Failed with message: " << #error_message << std::endl;\
      exit(-1);\
    }\
  }
#endif

#define MN_REQUIRE(condition, error_message) {\
    if(!condition) {\
      std::cerr << "----------Requirement Failed----------" << std::endl;\
      std::cerr << "Requirement failed in file: " << __FILE__ << std::endl;\
      std::cerr << "Requirement failed at line: " << __LINE__ << std::endl;\
      std::cerr << "Requirement failed inside function: " <<\
        __FUNCTION__ << std::endl;\
      std::cerr << "Failed with message: " << #error_message << std::endl;\
      exit(-2);\
    }\
}\

#define MN_WARNING(condition, warning_message) {\
  if(condition) {\
    std::cerr << "----------Warning----------" << std::endl;\
    std::cerr << "Warning in file: " << __FILE__ << std::endl;\
    std::cerr << "Warning at line: " << __LINE__ << std::endl;\
    std::cerr << "Warning inside function: " <<\
      __FUNCTION__ << std::endl;\
    std::cerr << "Warning message: " << #warning_message << std::endl;\
  }\
}\



} // macros
} // common 
} // mnyrve

#endif

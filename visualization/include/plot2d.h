#ifndef PLOT2D_H
#define PLOT2D_H

#include "common/include/error_macros.h"
#include "common/include/types.h"
#include "third_party/Eigen/Dense"
#include "utility/include/path_util.h"

#include "Python.h"

#include <iostream>
#include <fstream>
#include <string>

namespace mnyrve {
namespace visualization {

class Plot2d {

  public:
    Plot2d();
    void PlotSimple(Eigen::VectorXd x, Eigen::VectorXd y);
    void PlotComplete(
        Eigen::VectorXd x,
        Eigen::VectorXd y,
        mnyrve::common::types::PlotDetails);

};

} // visualization
} // mnyrve

#endif

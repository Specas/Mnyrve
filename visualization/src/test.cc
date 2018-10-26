#include "third_party/Eigen/Dense"
#include "visualization/include/plot2d.h"

#include <iostream>

namespace mnyrve {
namespace visualization {



} // visualization
} // mnyrve

int main() {

  mnyrve::visualization::Plot2d plotter;
  std::cout << "Starts" << std::endl;
  Eigen::VectorXd x(5);
  Eigen::VectorXd y(5);
  x << 0, 1, 2, 3, 4;
  y << 1, 1, 3, 4, 5;
  plotter.PlotSimple(x, y);

  return 0;

}

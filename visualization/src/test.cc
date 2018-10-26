#include "third_party/Eigen/Dense"
#include "visualization/include/plot2d.h"

#include <iostream>

namespace mnyrve {
namespace visualization {


} // visualization
} // mnyrve

int main() {

  mnyrve::visualization::Plot2d plotter;
  Eigen::VectorXd x(5);
  Eigen::VectorXd y(5);
  x << 0, 1, 2, 3, 4;
  y << 1, 1, 3, 4, 1;
  mnyrve::common::types::PlotDetails plot_details = {};
  plot_details.figure_title = "Figure";
  plot_details.plot_title = "Plot";
  plot_details.x_label = "x";
  plot_details.y_label = "y";
  plot_details.fmt = 'g';
  plot_details.x_limits.lower = 0;
  plot_details.x_limits.upper = 5;
  plot_details.y_limits.lower = 0;
  plot_details.y_limits.upper = 6;


  plotter.PlotComplete(x, y, plot_details);

  return 0;

}

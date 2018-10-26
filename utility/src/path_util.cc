#include "utility/include/path_util.h"

namespace mnyrve {
namespace utility {

std::string GetCurrentDirectory() {

  std::ifstream path_file("tools/data/mnyrve_path.txt");

  if (!path_file) {
    std::cerr << "Unable to open mnyrve_path.txt" << std::endl;
    exit(-3);
  }

  std::string path;
  std::getline(path_file, path);
  return path;

}



} // namespace mnyrve 
} // namespace utility

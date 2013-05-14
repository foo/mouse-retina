#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "../load-cubes/grid.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"
#include "../image/from-grid.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  dataset d(dataset_dir);
  grid g(d);

  image i = from_grid(g, 10, 300, 10, 300, 100);

  pgm_export(i, boost::filesystem::path("../output/filters/original.pgm"));
  
  return 0;
}

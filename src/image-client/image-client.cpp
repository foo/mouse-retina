#include <iostream>
#include <cassert>

#include "../load-cubes/grid.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"
#include "../image/from-grid.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  dataset d(dataset_dir);
  grid g(d);
  image i = from_grid(g, 10, 300, 10, 300, 10);
  std::cerr << "Successfully loaded image from grid" << std::endl;
  
  pgm_export(i,
      boost::filesystem::path("../output/video/white_rect.pgm"));
  std::cerr << "Successfully exported slice of tissue." << std::endl;
  return 0;
}

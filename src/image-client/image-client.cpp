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

  for(int z = 0; z < cube::dim*g.size_z; ++z)
  {
    std::cout << "Processing z coordinate " << z << std::endl;
    image i = from_grid(g, 10, 300, 10, 300, z);
    std::cout << "Successfully loaded image from grid" << std::endl;

    std::stringstream ss;
    ss << "../output/video/slice" << z << ".pgm";
    
    pgm_export(i,
      boost::filesystem::path(ss.str()));
    std::cout << "Successfully exported slice of tissue." << std::endl;
  }
  return 0;
}

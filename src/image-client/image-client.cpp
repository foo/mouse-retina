#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "../load-cubes/grid.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"
#include "../load-cubes/cross-section.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_large";
  dataset_files d(dataset_dir);
  grid g(d);

  for(int z = 0; z < cube::dim*g.size_z; ++z)
  {
    if(z % cube::dim == 0)
    {
      const int useless_z = (z / cube::dim) - 1;

      g.unload_z_lower_than(g.min_z + useless_z);
    }
    
    std::cout << "Processing z coordinate " << z << std::endl;
    image i = cross_section(g, 10, 600, 10, 600, z);
    std::cout << "Successfully loaded image from grid" << std::endl;

    std::stringstream ss;
    ss << "../output/video/slice" << z << ".pgm";
    
    pgm_export(i,
      boost::filesystem::path(ss.str()));
    std::cout << "Successfully exported slice of tissue." << std::endl;
  }
  return 0;
}

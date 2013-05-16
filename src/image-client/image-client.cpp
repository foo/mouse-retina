#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "../dataset/dataset.hpp"
#include "../dataset/cross-section.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_large";
  dataset d(dataset_dir);

  for(int z = 0; z < cube::dim*d.size_z; ++z)
  {
    if(z % cube::dim == 0)
    {
      const int useless_z = (z / cube::dim) - 1;

      d.unload_z_lower_than(d.min_z + useless_z);
    }
    
    std::cout << "Processing z coordinate " << z << std::endl;
    image i = cross_section(d, 10, 600, 10, 600, z);
    std::cout << "Successfully loaded image from grid" << std::endl;

    std::stringstream ss;
    ss << "../output/video/slice" << z << ".pgm";
    
    pgm_export(i,
      boost::filesystem::path(ss.str()));
    std::cout << "Successfully exported slice of tissue." << std::endl;
  }
  return 0;
}

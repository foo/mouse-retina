#include "load-cubes.hpp"

cube::cube(std::string filename)
{
  std::cerr << "Loading cube " << filename << "." << std::endl;

  std::ifstream cube_file;

  if(!cube_file.is_open())
  {
    std::cerr << "Cube exists." << std::endl;
  }
  else
  {
    std::cerr << "Cube does not exist." << std::endl;
  }
}

#include "load-cubes.hpp"

cube::cube(const char* const filename)
{
  std::ifstream cube_file(filename);

  if(!cube_file.is_open())
  {
    std::cerr
      << "Loading cube " << filename
      << " failed. File does not exists."
      << std::endl;
    exit(1);
  }
  else
  {
    std::cerr << "Cube found. Begin loading..." << std::endl;

    data.reserve(dim * dim * dim);

    std::copy(
      std::istream_iterator<unsigned char>(cube_file),
      std::istream_iterator<unsigned char>(),
      std::back_inserter(data));

    assert(data.size() == dim * dim * dim);
    
    std::cerr << "Loading done." << std::endl;
  }
}

unsigned char& cube::voxel(int x, int y, int z)
{
  return data[x + dim*y + dim*dim*z];
}


#include "cube.hpp"

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
  assert(0 <= x);
  assert(x <= dim);
  assert(0 <= y);
  assert(y <= dim);
  assert(0 <= z);
  assert(z <= dim);
  return data[x + dim*y + dim*dim*z];
}

unsigned char cube::voxel(int x, int y, int z) const
{
  assert(0 <= x);
  assert(x <= dim);
  assert(0 <= y);
  assert(y <= dim);
  assert(0 <= z);
  assert(z <= dim);
  return data[x + dim*y + dim*dim*z];
}


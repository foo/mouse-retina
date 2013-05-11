#include "cube.hpp"

cube::cube(const boost::filesystem::path& path)
{
  boost::filesystem::ifstream cube_file(path);

  if(!cube_file.is_open())
  {
    std::cerr
      << "Loading cube " << path
      << " failed. File does not exists."
      << std::endl;
    exit(1);
  }
  else
  {
    data.reserve(dim * dim * dim);

    // There are some ugly bits below.
    // First, we take raw pointer to vector: &data[0]
    // Then, we need to read UNSIGNED chars, but we do not want
    // to read signed chars and convert them to unsigned in following manner:
    //
    //    char c = ...;
    //    unsigned char uc = c;
    //
    // Code above loses the sign bit.
    //
    // However, following code does the right thing, which means
    // blindly copying sign bit as most significant bit of unsigned char.
    //
    //    char c = ...;
    //    unsigned char uc = reinterpret_cast<char>(c);
    //
    // reinterpret_cast below is equivalent cast for arrays

    cube_file.read(reinterpret_cast<char*>(&data[0]), dim * dim * dim);

    assert(cube_file.good());
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

std::vector<unsigned char>::const_iterator cube::voxel_iter(int x, int y, int z) const
{
  assert(0 <= x);
  assert(x <= dim);
  assert(0 <= y);
  assert(y <= dim);
  assert(0 <= z);
  assert(z <= dim);

  return data.begin() + x + dim*y + dim*dim*z;
}

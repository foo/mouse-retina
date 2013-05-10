#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <cassert>

class cube
{
public:
  static const int dim = 128;
  cube(const char* const filename);
  unsigned char& voxel(int x, int y, int z);
  unsigned char voxel(int x, int y, int z) const;
private:
  std::vector<unsigned char> data;
};


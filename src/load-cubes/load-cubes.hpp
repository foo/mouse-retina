#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>

class cube
{
public:
  static const int dim = 128;
  cube(const char* const filename);
  unsigned char& voxel(int x, int y, int z);
private:
  unsigned char data[dim * dim * dim];
};


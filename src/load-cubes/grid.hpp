#pragma once

#include <iostream>
#include <string>
#include <map>

#include "cube.hpp"

struct coord
{
  int x, y, z;
  coord(int X = -1, int Y = -1, int Z = -1)
    : x(X), y(Y), z(Z) {}
  bool operator<(const coord& c) const;
};

class grid
{
private:
  std::map<coord, cube> cube_cache;
public:
  grid(const char* const dataset);
  int cube_cache_size() const;
};

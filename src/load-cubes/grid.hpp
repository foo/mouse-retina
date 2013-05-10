#pragma once

#include <iostream>
#include <string>
#include <map>

#include "cube.hpp"
#include "coord.hpp"

class grid
{
private:
  std::map<coord, cube> cube_cache;
public:
  grid(const char* const dataset);
  int cube_cache_size() const;
};

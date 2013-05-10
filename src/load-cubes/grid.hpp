#pragma once

#include <iostream>
#include <string>
#include <map>

#include "cube.hpp"
#include "coord.hpp"
#include "dataset.hpp"

class grid
{
private:
  std::map<coord, cube> cube_cache;
public:
  grid(const dataset& ds);
  int cube_cache_size() const;
};

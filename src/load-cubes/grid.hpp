#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <boost/filesystem.hpp>

#include "cube.hpp"
#include "coord.hpp"
#include "dataset.hpp"

class grid
{
private:
  const dataset& ds;
  std::map<coord, cube> cube_cache;
public:
  grid(const dataset& ds);
  int cube_cache_size() const;
  const cube& get(const coord& c);
  void unload_from_cache(const coord& c);
  void unload_z_higher_than(int z_limit);
  void unload_z_lower_than(int z_limit);

  const int min_x, max_x, min_y, max_y, min_z, max_z;
  const int size_x, size_y, size_z;
};

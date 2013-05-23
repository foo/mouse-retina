#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>

#include "cube.hpp"
#include "coord.hpp"
#include "dataset_files.hpp"

class dataset
{
private:
  dataset_files ds_files;
  std::map<coord, cube> cube_cache;
public:
  dataset(const std::string& dataset_dir);
  int cube_cache_size() const;
  const cube& get_cube(const coord& c);
  const cube& get_cube(int x, int y, int z) { return get_cube(coord(x, y, z)); }
  void unload_from_cache(const coord& c);
  void unload_z_higher_than(int z_limit);
  void unload_z_lower_than(int z_limit);

  // values in cube numbers, not voxels
  // e.g. for two cubes x0007 and x0008 we have
  // max_x = 9, min_x = 7
  const int min_x, max_x, min_y, max_y, min_z, max_z;

  // size in number of cubes, not voxels
  const int size_x, size_y, size_z;
};

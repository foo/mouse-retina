#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include <climits>
#include <boost/filesystem.hpp>

#include "../load-cubes/coord.hpp"

class dataset
{
private:
  void populate_cube_files(const char* const dataset_dir);
  void find_min_and_max_coords();
  void check_if_dataset_has_holes();
public:
  void print_cube_files();
  std::map<coord, boost::filesystem::path> cube_files;
  dataset(const char* const dataset_dir);

  int min_x, max_x, min_y, max_y, min_z, max_z;
};

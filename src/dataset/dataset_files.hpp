#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include <climits>
#include <string>
#include <boost/filesystem.hpp>

#include "coord.hpp"

class dataset_files
{
private:
  void populate_cube_files(const std::string& dataset_dir);
  void find_min_and_max_coords();
  void check_if_dataset_has_holes();
public:
  void print_cube_files();
  std::map<coord, boost::filesystem::path> cube_files;
  dataset_files(const std::string& dataset_dir);

  int min_x, max_x, min_y, max_y, min_z, max_z;
};

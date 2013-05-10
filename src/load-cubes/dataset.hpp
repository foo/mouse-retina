#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include <boost/filesystem.hpp>

#include "../load-cubes/coord.hpp"

class dataset
{
private:
  void populate_cube_files(const char* const dataset_dir);
  void print_cube_files();
public:
  std::map<coord, boost::filesystem::path> cube_files;
  dataset(const char* const dataset_dir);
};

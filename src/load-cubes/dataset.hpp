#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "grid.hpp"

class dataset
{
private:
  void parse_config(std::ifstream& in);
  void print_config();
public:
  dataset(const char* const directory);
  std::string experiment_name;
  float scale_x;
  float scale_y;
  float scale_z;
  int boundary_x;
  int boundary_y;
  int boundary_z;
  int magnification;
  grid grid_data;
};

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class knossos_config
{
private:
  void parse_file(std::ifstream& in);
  bool parse_experiment_var(std::istringstream& iss);
  bool parse_scale_var(std::istringstream& iss);
  bool parse_boundary_var(std::istringstream& iss);
  bool parse_magnification_var(std::istringstream& iss);
public:
  knossos_config(const std::string& directory);
  void print_config() const;
  std::string experiment_name;
  float scale_x;
  float scale_y;
  float scale_z;
  int boundary_x;
  int boundary_y;
  int boundary_z;
  int magnification;
};

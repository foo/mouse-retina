#pragma once

#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <boost/program_options.hpp>

class options
{
public:
  options(
    const boost::program_options::options_description&,
    int argc,
    const char* const argv[]);

  int int_var(const std::string& var) const;
  std::string string_var(const std::string& var) const;
private:
  boost::program_options::options_description desc;
  boost::program_options::variables_map vars;

  void add_default_options(const std::string& binary_name);

  void read_cmd_line_args(int argc, const char* const argv[]);
  void read_config_file(const std::string& filename);
  bool var_present(const std::string& var) const;
  void check_presence(const std::string& var) const;
};

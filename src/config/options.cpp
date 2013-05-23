#include "options.hpp"

namespace po = boost::program_options;

// Reads options from command line to check if config file name is specified.
// Then reads either specified config or default config (name can be taken
//  from argv[0])
// Command line arguments has precedence over config file options.

options::options(
  const po::options_description& options_desc,
  int argc, const char* const argv[])
  : desc(options_desc)
{
  add_default_options(argv[0]);
  read_cmd_line_args(argc, argv);

  read_config_file(string_var("config-file"));
  
  if(var_present("help"))
  {
    std::cerr << desc << std::endl;
    exit(0);
  }
}

void options::add_default_options(const std::string& binary_name)
{
  // two helpful options that are used in every client program
  desc.add_options()
    ("config-file,c",
      po::value<std::string>()->default_value(
	binary_name + ".cfg"),
      "Set path for config file. You can specify the same variables in both command line arguments and config file. Variables set in command line has precedence over those set in config file.")

    ("help,h",
    "Produce this help message.");
}

void options::read_cmd_line_args(int argc, const char* const argv[])
{
  po::store(po::parse_command_line(argc, argv, desc), vars);
  po::notify(vars);
}

void options::read_config_file(const std::string& settings_filename)
{
  std::ifstream settings_file(settings_filename);
  if(!settings_file.is_open())
  {
    std::cerr
      << "Warning: loading configuration file <" << settings_filename
      << "> failed. File does not exists. This is not a big deal if you have sane defaults or you specify enough parameters in command line."
      << std::endl;
  }
  po::store(po::parse_config_file(settings_file, desc), vars);
}

float options::float_var(const std::string& var) const
{
  check_presence(var);
  return vars[var].as<float>();
}

int options::int_var(const std::string& var) const
{
  check_presence(var);
  return vars[var].as<int>();
}

std::string options::string_var(const std::string& var) const
{
  check_presence(var);
  return vars[var].as<std::string>();
}

bool options::var_present(const std::string& var) const
{
  return vars.count(var) != 0;
}

void options::check_presence(const std::string& var) const
{
  if(!var_present(var))
  {
    if(var == "config-file")
    {
      // this branch is for avoiding infinite recursion
      // when config-file variable is not present
      std::cerr
	<< "Cannot find config file variable. Options module internal error."
	<< std::endl;
    }
    else
    {
      std::cerr << "Variable " << var << " was not set. Used config file: "
		<< string_var("config-file") << std::endl;
      exit(1);
    }
  }
}

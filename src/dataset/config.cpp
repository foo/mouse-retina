#include "config.hpp"

config::config(const char* const directory)
{
  std::ifstream conf(std::string(directory) + "/knossos.conf");
  parse_file(conf);
}

void config::parse_file(std::ifstream& in)
{
  std::string line;
  while(std::getline(in, line))
  {
    std::istringstream iss(line);
    std::string variable;

    if (!(iss >> variable))
      continue;    // in case of empty line

    bool parse_line_successful = true;
    
    if(variable == "experiment")
      parse_line_successful = parse_experiment_var(iss);
    else if(variable == "scale")
      parse_line_successful = parse_scale_var(iss);
    else if(variable == "boundary")
      parse_line_successful = parse_boundary_var(iss);
    else if(variable == "magnification")
      parse_line_successful = parse_magnification_var(iss);
    else
    {
      std::cerr
	<< "Parse config: unknown variable: <"
	<< variable << ">" << std::endl;
      exit(0);
    }

    if(!parse_line_successful)
    {
      std::cerr
	<< "Parse config: error reading line:\n\t"
	<< line << std::endl;
      exit(0);
    }
  }
}

void config::print_config() const
{
  std::cout << "experiment name " << experiment_name << ";\n"
	    << "scale x " << scale_x << ";\n"
	    << "scale y " << scale_y << ";\n"
	    << "scale z " << scale_z << ";\n"
	    << "boundary x " << boundary_x << ";\n"
	    << "boundary y " << boundary_y << ";\n"
	    << "boundary z " << boundary_z << ";\n"
	    << "magnification " << magnification << ";"
	    << std::endl;
}

bool config::parse_experiment_var(std::istringstream& iss)
{
  std::string secondary_variable;
  iss >> secondary_variable;
      
  // first character of third string is "
  iss.ignore(1, '\"');
      
  iss >> experiment_name;

  // last two characters of third string are ";
  experiment_name.resize(experiment_name.size() - 2);
  
  return iss.good();
}

bool config::parse_scale_var(std::istringstream& iss)
{
  std::string secondary_variable;
  iss >> secondary_variable;
  if(secondary_variable == "x")
  {
    iss >> scale_x;
    return iss.good();
  }
  else if(secondary_variable == "y")
  {
    iss >> scale_y;
    return iss.good();
  }
  else if(secondary_variable == "z")
  {
    iss >> scale_z;
    return iss.good();
  }
  else
  {
    return false;
  }
}

bool config::parse_boundary_var(std::istringstream& iss)
{
  std::string secondary_variable;
  iss >> secondary_variable;
  if(secondary_variable == "x")
  {
    iss >> boundary_x;
    return iss.good();
  }
  else if(secondary_variable == "y")
  {
    iss >> boundary_y;
    return iss.good();
  }
  else if(secondary_variable == "z")
  {
    iss >> boundary_z;
    return iss.good();
  }
  else
    return false;
}

bool config::parse_magnification_var(std::istringstream& iss)
{
  iss >> magnification;
  return iss.good();
}


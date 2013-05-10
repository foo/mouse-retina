#include "dataset.hpp"

dataset::dataset(const char* const directory)
  : grid_data(directory)
{
  std::ifstream conf(std::string(directory) + "/knossos.conf");
  parse_config(conf);
  print_config();
}

void dataset::print_config()
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

void dataset::parse_config(std::ifstream& in)
{
  std::string line;
  while (std::getline(in, line))
  {
    std::istringstream iss(line);
    std::string variable;
    std::string secondary_variable;

    if (!(iss >> variable))
      continue;    // empty line
    
    if(variable == "experiment")
    {
      iss >> secondary_variable;
      
      // first character of third string is "
      iss.ignore(1, '\"');
      
      iss >> experiment_name;

      // last two characters of third string are ";
      experiment_name.resize(experiment_name.size() - 2);
    }
    else if(variable == "scale")
    {
      iss >> secondary_variable;
      if(secondary_variable == "x")
	iss >> scale_x;
      else if(secondary_variable == "y")
	iss >> scale_y;
      else if(secondary_variable == "z")
	iss >> scale_z;
      else
      {
	std::cerr
	  << "Parse config: unknown secondary scale variable: <"
	  << variable << ">" << std::endl;
	exit(0);
      }
    }
    else if(variable == "boundary")
    {
      iss >> secondary_variable;
      if(secondary_variable == "x")
	iss >> boundary_x;
      else if(secondary_variable == "y")
	iss >> boundary_y;
      else if(secondary_variable == "z")
	iss >> boundary_z;
      else
      {
	std::cerr
	  << "Parse config: unknown secondary boundary variable: <"
	  << variable << ">" << std::endl;
	exit(0);
      }
    }
    else if(variable == "magnification")
    {
      iss >> magnification;
    }
    else
    {
      std::cerr
	<< "Parse config: unknown variable: <"
	<< variable << ">" << std::endl;
      exit(0);
    }
  }
};

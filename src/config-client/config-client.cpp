#include <iostream>
#include <cassert>

#include "../config/knossos-config.hpp"
#include "../config/options.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
  po::options_description opt_desc("Config file client reads knossos config file in dataset that is specified by either command line or config file. Avaliable options");

  opt_desc.add_options()
    ("dataset-path,d",
      po::value<std::string>()->default_value("../images/e1088_mag1_small"),
      "Specify path to dataset in Knossos format.");

  options opts(opt_desc, argc, argv);
  
  knossos_config c(opts.string_var("dataset-path"));
  c.print_config();

  return 0;
}


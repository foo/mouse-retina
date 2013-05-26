#include <iostream>
#include <cassert>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
namespace mpi = boost::mpi;

#include "../config/options.hpp"

#include "../traverser/manager.hpp"
#include "../traverser/worker.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
  mpi::environment env(argc, argv);
  mpi::communicator world;
  
  po::options_description opt_desc("Traverser client");

  opt_desc.add_options()
    ("dataset-path,d",
      po::value<std::string>()->default_value("../images/e1088_mag1_small"),
      "Specify path to dataset in Knossos format.");

  options opts(opt_desc, argc, argv);
  
  std::cout << "Process rank: " << world.rank() << '\n'
	    << "Communicator size: " << world.size() << std::endl;
   
  return 0;
}


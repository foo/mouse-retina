#include <iostream>
#include <cassert>
#include <mpi.h>

#include "../config/options.hpp"

#include "../traverser/manager.hpp"
#include "../traverser/worker.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);
  
  po::options_description opt_desc("Traverser client");

  opt_desc.add_options()
    ("dataset-path,d",
      po::value<std::string>()->default_value("../images/e1088_mag1_small"),
      "Specify path to dataset in Knossos format.");

  options opts(opt_desc, argc, argv);
  
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int comm_size;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  std::cout << "Process rank: " << rank << '\n'
	    << "Communicator size: " << comm_size << std::endl;

  return 0;
}


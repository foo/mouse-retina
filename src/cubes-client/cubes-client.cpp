#include <iostream>

#include "../load-cubes/cube.hpp"
#include "../load-cubes/grid.hpp"
#include "../load-cubes/config.hpp"
#include "../load-cubes/dataset.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  grid g(dataset_dir);
  config c(dataset_dir);
  c.print_config();
  std::cerr << g.cube_cache_size() << std::endl;
  dataset d(dataset_dir);
  d.print_cube_files();

  std::cerr << "min x: " << d.min_x << '\n'
	    << "max x: " << d.max_x << '\n'
	    << "min y: " << d.min_y << '\n'
	    << "max y: " << d.max_y << '\n'
	    << "min z: " << d.min_z << '\n'
	    << "max z: " << d.max_z << '\n';

  return 0;
}


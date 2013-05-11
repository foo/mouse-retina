#include <iostream>
#include <cassert>

#include "../load-cubes/cube.hpp"
#include "../load-cubes/grid.hpp"
#include "../load-cubes/config.hpp"
#include "../load-cubes/dataset.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  config c(dataset_dir);
  c.print_config();
  dataset d(dataset_dir);
  d.print_cube_files();

  std::cerr << "min x: " << d.min_x << '\n'
	    << "max x: " << d.max_x << '\n'
	    << "min y: " << d.min_y << '\n'
	    << "max y: " << d.max_y << '\n'
	    << "min z: " << d.min_z << '\n'
	    << "max z: " << d.max_z << '\n';

  grid g(d);
  std::cerr << "Cube cache size = " << g.cube_cache_size() << std::endl;

  {
    const cube& cb = g.get(coord(5, 7, 6));
    std::cerr << "Voxel from cube (5, 7, 6) at (5,5,5) = "
	      << cb.voxel(5, 5, 5) << std::endl;
  }
  
  std::cerr << "Cube cache size = " << g.cube_cache_size() << std::endl;

  {
    const cube& cb = g.get(coord(6, 7, 6));
    std::cerr << "Voxel from cube (6, 7, 6) at (15,5,5) = "
	      << cb.voxel(15, 5, 5) << std::endl;
  }

  {
    const cube& cb = g.get(coord(6, 7, 6));
    std::cerr << "Voxel from cube (6, 7, 6) at (10,10,10) = "
	      << cb.voxel(10, 10, 10) << std::endl;
  }
  
  std::cerr << "Cube cache size = " << g.cube_cache_size() << std::endl;

  
  {
    const cube& cb = g.get(coord(5, 7, 5));
    std::cerr << "Voxel from cube (5, 7, 5) at (127,127,127) = "
	      << cb.voxel(127,127,127) << std::endl;
    assert(cb.voxel(127,127,127) != cb.voxel(127,127,126));
  }
  
  std::cerr << "Cube cache size = " << g.cube_cache_size() << std::endl;

  return 0;
}


#include <iostream>
#include <cassert>

#include "../dataset/cube.hpp"
#include "../dataset/dataset.hpp"
#include "../dataset/config.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  config c(dataset_dir);
  c.print_config();
  dataset d(dataset_dir);

  std::cerr << "min x: " << d.min_x << '\n'
	    << "max x: " << d.max_x << '\n'
	    << "min y: " << d.min_y << '\n'
	    << "max y: " << d.max_y << '\n'
	    << "min z: " << d.min_z << '\n'
	    << "max z: " << d.max_z << '\n';

  std::cerr << "Cube cache size = " << d.cube_cache_size() << std::endl;

  {
    const cube& cb = d.get_cube(coord(5, 7, 6));
    std::cerr << "Voxel from cube (5, 7, 6) at (5,5,5) = "
	      << cb.voxel(5, 5, 5) << std::endl;
  }
  
  std::cerr << "Cube cache size = " << d.cube_cache_size() << std::endl;

  {
    const cube& cb = d.get_cube(coord(6, 7, 6));
    std::cerr << "Voxel from cube (6, 7, 6) at (15,5,5) = "
	      << cb.voxel(15, 5, 5) << std::endl;
  }

  {
    const cube& cb = d.get_cube(coord(6, 7, 6));
    std::cerr << "Voxel from cube (6, 7, 6) at (10,10,10) = "
	      << cb.voxel(10, 10, 10) << std::endl;
  }
  
  std::cerr << "Cube cache size = " << d.cube_cache_size() << std::endl;
  
  {
    const cube& cb = d.get_cube(coord(5, 7, 5));
    std::cerr << "Voxel from cube (5, 7, 5) at (127,127,127) = "
	      << cb.voxel(127,127,127) << std::endl;
    assert(cb.voxel(127,127,127) != cb.voxel(127,127,126));
  }
  
  std::cerr << "Cube cache size = " << d.cube_cache_size() << std::endl;
  
  {
    const cube& cb = d.get_cube(coord(5, 7, 7));
    std::cerr << "Voxel from cube (5, 7, 7) at (127,127,127) = "
	      << cb.voxel(127,127,127) << std::endl;
  }
  
  std::cerr << "Cube cache size = " << d.cube_cache_size() << std::endl;

  std::cerr << "Unload cubes with z higher than 5" << std::endl;
  d.unload_z_higher_than(5);
  
  std::cerr << "Cube cache size = " << d.cube_cache_size() << std::endl;

  return 0;
}

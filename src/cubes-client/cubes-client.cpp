#include <iostream>

#include "../load-cubes/cube.hpp"
#include "../load-cubes/grid.hpp"
#include "../load-cubes/dataset.hpp"

int main(int argc, char* argv[])
{
  dataset d("../images/e1088_mag1_small");
  std::cerr << d.grid_data.cube_cache_size() << std::endl;

  return 0;
}


#include <iostream>

#include "../load-cubes/cube.hpp"
#include "../load-cubes/grid.hpp"

int main(int argc, char* argv[])
{
  grid g("../images/e1088_mag1_small");

  std::cerr << g.cube_cache_size() << std::endl;
  return 0;
}


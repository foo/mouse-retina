#include <iostream>

#include "../load-cubes/cube.hpp"
#include "../load-cubes/grid.hpp"

int main(int argc, char* argv[])
{
  char cube_path[] = "../images/e1088_mag1_small/x0005/y0007/z0007/070317_e1088_x0005_y0007_z0007.raw";
  cube c(cube_path);

  grid g("../images/e1088_mag1_small");
  return 0;
}


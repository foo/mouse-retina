#include "grid.hpp"

grid::grid(const char* const dataset)
{
  std::cerr << "Loading grid from dataset " << dataset << "." << std::endl;

  std::string cube_path = std::string(dataset) + "/x0005/y0007/z0007/070317_e1088_x0005_y0007_z0007.raw";

  cube c(cube_path.c_str());
  cube_cache.insert(std::make_pair(coord(1, 1, 1), std::move(c)));
}

int grid::cube_cache_size() const
{
  return cube_cache.size();
}


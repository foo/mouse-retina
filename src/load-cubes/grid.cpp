#include "grid.hpp"

grid::grid(const dataset& ds)
{
  std::string cube_path = (++ds.cube_files.begin())->second.string();

  cube c(cube_path.c_str());
  cube_cache.insert(std::make_pair(coord(1, 1, 1), std::move(c)));
}

int grid::cube_cache_size() const
{
  return cube_cache.size();
}


#include "grid.hpp"

grid::grid(const char* const dataset)
{
  std::cerr << "Loading grid from dataset " << dataset << "." << std::endl;

  std::string cube_path = std::string(dataset) + "/x0005/y0007/z0007/070317_e1088_x0005_y0007_z0007.raw";

  cube c(cube_path.c_str());
  cube_cache.insert(std::make_pair(coord(1, 1, 1), c));
}

int grid::cube_cache_size() const
{
  return cube_cache.size();
}

bool coord::operator<(const coord& c) const
{
  if(x < c.x)
    return true;
  else if (c.x < x)
    return false;
  else //if(x == c.x)
  {
    if(y < c.y)
      return true;
    else if (c.y < y)
      return false;
    else //if(y == c.y)
    {
      if(z < c.z)
	return true;
      else if (c.z < z)
	return false;
      else //if(z == c.z)
      {
	return true;
      }
    }
  }
}

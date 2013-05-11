#include "from-grid.hpp"

image from_grid(grid& g, int x1, int x2, int y1, int y2, int z)
{
  assert(x1 >= 0);
  assert(x1 <= x2);

  assert(y1 >= 0);
  assert(y1 <= y2);
  
  return image(); // equivalent to std::move(image)
}

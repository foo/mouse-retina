#include "from-grid.hpp"

image from_grid(grid& g, int x1, int x2, int y1, int y2, int z)
{
  assert(x1 >= 0);
  assert(y1 >= 0);
  assert(z  >= 0);

  assert(x1 <= x2);
  assert(y1 <= y2);

  assert(x2 < g.size_x * cube::dim);
  assert(y2 < g.size_y * cube::dim);
  assert(z  < g.size_z * cube::dim);

  image i;
  i.allocate(x2 - x1, y2 - y1);

  return i; // equivalent to std::move(image)
}

#include "image.hpp"

image::image()
  : w(-1), h(-1)
{
  
}

void image::allocate(int width, int height)
{
  assert(width > 0);
  assert(height > 0);
  assert(!initialized());
  
  w = width;
  h = height;

  data.reserve(w * h);
  std::fill_n(
    std::back_inserter(data),
    w * h,
    static_cast<unsigned char>(255));
}

unsigned char& image::get(int x, int y)
{
  assert(0 <= x);
  assert(x < w);
  assert(0 <= y);
  assert(y < h);
  return data[x + w*y];
}

unsigned char image::get(int x, int y) const
{
  assert(0 <= x);
  assert(x < w);
  assert(0 <= y);
  assert(y < h);
  return data[x + w*y];
}

bool image::pixel_inside(int x, int y) const
{
  return x >= 0 && y >= 0 && x < w && y < h;
}

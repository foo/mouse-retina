#include "image.hpp"

image::image()
  : w(-1), h(-1)
{
  
}

image::image(const image& i)
  : w(i.w), h(i.h), data(i.data)
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

unsigned char& image::pixel(int x, int y)
{
  assert(is_inside(x, y));
  return data[x + w*y];
}

unsigned char image::pixel(int x, int y) const
{
  assert(is_inside(x, y));
  return data[x + w*y];
}

bool image::is_inside(int x, int y) const
{
  return x >= 0 && y >= 0 && x < w && y < h;
}

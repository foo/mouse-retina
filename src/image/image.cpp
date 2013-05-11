#include "image.hpp"

void image::white_rect(int w, int h)
{
  width = w;
  height = h;

  data.reserve(w * h);
  std::fill_n(
    std::back_inserter(data),
    w * h,
    static_cast<unsigned char>(255));
}

unsigned char& image::get(int x, int y)
{
  assert(0 <= x);
  assert(x < width);
  assert(0 <= y);
  assert(y < height);
  return data[x + width*y];
}

unsigned char image::get(int x, int y) const
{
  assert(0 <= x);
  assert(x < width);
  assert(0 <= y);
  assert(y < height);
  return data[x + width*y];
}

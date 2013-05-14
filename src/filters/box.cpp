#include "box.hpp"

box_filter::box_filter(const std::vector<int>& filter_data)
  : filter(filter_data)
{
  // http://www.cplusplus.com/reference/cmath/sqrt/
  // in C++11, which we are using here there are overloads
  // for sqrt for integral types
  dim = sqrt(filter_data.size());
  
  assert(dim*dim == filter_data.size());
}

int box_filter::apply_to_pixel(const image& i, int cx, int cy) const
{
  int sum = 0;
  int denom = 0;

  const int offset = (dim - 1) / 2;

  for(int x = -offset; x <= offset; x++)
    for(int y = -offset; y <= offset; y++)
    {
      if(i.pixel_inside(x, y))
      {
	denom += get(x, y);
	sum += get(x, y) * i.get(x, y);
      }
    }
  
  return sum / denom;
}

int box_filter::get(int x, int y) const
{
  return filter[x + dim*y];
}

image box_filter::apply_naive(const image& i) const
{
  image out;
  out.allocate(i.width(), i.height());
  
  for(int x = 0; x < i.width(); ++x)
    for(int y = 0; y < i.height(); ++y)
    {
      out.get(x, y) = static_cast<unsigned char>(
	apply_to_pixel(i, x, y));
    }

  return out;
}

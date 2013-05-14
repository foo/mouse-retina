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
      const int image_x = cx + x;
      const int image_y = cy + y;

      const int filter_x = x + offset;
      const int filter_y = y + offset;
      
      if(i.pixel_inside(image_x, image_y))
      {
	denom += get(filter_x, filter_y);
	sum += get(filter_x, filter_y) * i.get(image_x, image_y);
      }
    }

  int result;
  
  if(denom != 0)
    result = sum / denom;
  else
    result = sum;

  if(result < 0) result = 0;
  if(result > 255) result = 255;

  return result;
}

int box_filter::get(int x, int y) const
{
  assert(0 <= x);
  assert(x < dim);
  assert(0 <= y);
  assert(y < dim);
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

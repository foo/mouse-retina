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

float box_filter::apply_to_pixel_no_rounding(const image& i, int cx, int cy) const
{
  float sum = 0;
  float denom = 0;

  const int offset = (dim - 1) / 2;

  for(int x = -offset; x <= offset; x++)
    for(int y = -offset; y <= offset; y++)
    {
      const int image_x = cx + x;
      const int image_y = cy + y;

      const int filter_x = x + offset;
      const int filter_y = y + offset;
      
      if(i.is_inside(image_x, image_y))
      {
	denom += element(filter_x, filter_y);
	sum += element(filter_x, filter_y) * i.pixel(image_x, image_y);
      }
    }

  if(denom != 0)
    return sum / denom;
  else
    return sum;
}

int box_filter::apply_to_pixel(const image& i, int cx, int cy) const
{
  float result = apply_to_pixel_no_rounding(i, cx, cy);
  if(result < 0) return 0;
  if(result > 255) return 255;

  return static_cast<int>(result);
}

int box_filter::element(int x, int y) const
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
      out.pixel(x, y) = static_cast<unsigned char>(
	apply_to_pixel(i, x, y));
    }

  return out;
}

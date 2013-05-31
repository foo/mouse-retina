#include "sobel.hpp"

image sobel(const image& i)
{
  image out;
  out.allocate(i.width(), i.height());

  for(int x = 0; x < i.width(); ++x)
    for(int y = 0; y < i.height(); ++y)
    {
      const std::pair<float, float> p = sobel_vector(i, x, y);
      
      out.pixel(x,y) = 
	sqrtf(p.first*p.first + p.second*p.second);
    }
  
  return out;
}

std::pair<float, float> sobel_vector(const image& i, int x, int y)
{
  box_filter vertical_gradient(
    {    1,  2,  1,
	 0,  0,  0,
	-1, -2, -1
    });

  box_filter horizontal_gradient(
    {   1,  0, -1,
	2,  0, -2,
	1,  0, -1
    });

  const int vertical = vertical_gradient.apply_to_pixel(i, x, y);
  const int horizontal = horizontal_gradient.apply_to_pixel(i, x, y);

  return std::make_pair(vertical, horizontal);
}

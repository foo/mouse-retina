#include "sobel.hpp"

image sobel(const image& i)
{
  image out;
  out.allocate(i.width(), i.height());

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

  for(int x = 0; x < i.width(); ++x)
    for(int y = 0; y < i.height(); ++y)
    {
      const int vertical = vertical_gradient.apply_to_pixel(i, x, y);
      const int horizontal = horizontal_gradient.apply_to_pixel(i, x, y);
      
      out.pixel(x,y) = 
	sqrtf(vertical*vertical + horizontal*horizontal);
    }
  
  return out;
}

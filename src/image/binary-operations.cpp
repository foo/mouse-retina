#include "binary-operations.hpp"

void negation_in_place(image& i)
{
  assert(is_binary_image(i));

  for(int x = 0; x < i.width(); ++x)
    for(int y = 0; y < i.height(); ++y)
      if(i.pixel(x, y) == 0)
	i.pixel(x, y) = 255;
      else
	i.pixel(x, y) = 0;
}

image negation(const image& i)
{
  image out(i);
  negation_in_place(out);
  return out;
}

bool is_binary_image(const image& i)
{
  for(int x = 0; x < i.width(); ++x)
    for(int y = 0; y < i.height(); ++y)
      if(i.pixel(x, y) != 0 && i.pixel(x, y) != 255)
	return false;
  return true;
}

#include "threshold.hpp"

void threshold_in_place(image& i, int threshold_value)
{
  for(int x = 0; x < i.width(); ++x)
    for(int y = 0; y < i.height(); ++y)
      if(i.pixel(x, y) < threshold_value)
	i.pixel(x, y) = 0;
      else
	i.pixel(x, y) = 255;
}

image threshold(const image& i, int threshold_value)
{
  image out(i);
  threshold_in_place(out, threshold_value);
  return out;
}

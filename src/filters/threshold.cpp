#include "threshold.hpp"

void threshold_in_place(image& i, int threshold_value)
{
  for(int x = 0; x < i.width(); ++x)
    for(int y = 0; y < i.height(); ++y)
      if(i.get(x, y) < threshold_value)
	i.get(x, y) = 0;
      else
	i.get(x, y) = 255;
}

image threshold(const image& i, int threshold_value)
{
  image out(i);
  threshold_in_place(out, threshold_value);
  return out;
}

#include "sharpen.hpp"

image sharpen(const image& i)
{
  box_filter sharpen(
    {   -1,  -1,  -1,
	-1,   9,  -1,
	-1,  -1,  -1  });

  return sharpen.apply_naive(i);
}

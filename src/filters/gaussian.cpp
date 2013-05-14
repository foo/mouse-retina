#include "gaussian.hpp"

image gaussian5x5(const image& i)
{
  // delta is 1.4
  box_filter gaussian(
    {   2,  4,  5,  4,  2,
	4,  9, 12,  9,  4,
	5, 12, 15, 12,  5,
	4,  9, 12,  9,  4,
	2,  4,  5,  4,  2  });

  return gaussian.apply_naive(i);
}

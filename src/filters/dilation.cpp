#include "dilation.hpp"

image dilation(const image& i)
{
  box_filter structural_element(
    {   0,  1,  0,
	1,  1,  0,
	0,  0,  0  });

  return threshold(structural_element.apply_naive(i), 1);
}

image erosion(const image& i)
{
  // unimplemented
  
  return i;
}

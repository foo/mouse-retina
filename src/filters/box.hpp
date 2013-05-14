#pragma once

#include <vector>
#include <cassert>
#include "../image/image.hpp"

class box_filter
{
private:
  int dim;
  std::vector<int> filter;
  int get(int x, int y) const;
public:
  box_filter(const std::vector<int>& filter_data);

  // apply_to_pixel is useful e.g. in Sobel filter
  int apply_to_pixel(const image& i, int px, int py) const;
  image apply_naive(const image& i) const;
};


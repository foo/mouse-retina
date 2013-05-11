#pragma once

#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

class image
{
public:
  void white_rect(int w, int h);
  int width, height;
  unsigned char& get(int x, int y);
  unsigned char get(int x, int y) const;
  std::vector<unsigned char> data;
};

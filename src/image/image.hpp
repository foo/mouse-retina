#pragma once

#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

class image
{
private:
  int w, h;
public:
  image();
  void allocate(int width, int height);
  unsigned char& get(int x, int y);
  unsigned char get(int x, int y) const;
  int width() const { return w; }
  int height() const { return h; }
  bool initialized() const { return w != -1; }
  std::vector<unsigned char> data;
  bool pixel_inside(int x, int y) const;
};

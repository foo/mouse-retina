#include "gaussian.hpp"

// very simple implementation of gaussian filter.
// delta is 1.4, which results in box filter like this:
//
// 2  4  5  4  2
// 4  9 12  9  4
// 5 12 15 12  5
// 4  9 12  9  4
// 2  4  5  4  2

image gaussian(const image& i)
{
  image out;
  out.allocate(i.width(), i.height());

  for(int x = 2; x < i.width() - 2; ++x)
    for(int y = 2; y < i.height() - 2; ++y)
    {
      const int g00 = 2 * i.get(x - 2, y - 2);
      const int g10 = 4 * i.get(x - 1, y - 2);
      const int g20 = 5 * i.get(x    , y - 2);
      const int g30 = 4 * i.get(x + 1, y - 2);
      const int g40 = 2 * i.get(x + 2, y - 2);

      const int g01 = 4 * i.get(x - 2, y - 1);
      const int g11 = 9 * i.get(x - 1, y - 1);
      const int g21 = 12* i.get(x    , y - 1);
      const int g31 = 9 * i.get(x + 1, y - 1);
      const int g41 = 4 * i.get(x + 2, y - 1);

      const int g02 = 5 * i.get(x - 2, y);
      const int g12 = 12* i.get(x - 1, y);
      const int g22 = 15* i.get(x    , y);
      const int g32 = 12* i.get(x + 1, y);
      const int g42 = 5 * i.get(x + 2, y);

      const int g03 = 4 * i.get(x - 2, y + 1);
      const int g13 = 9 * i.get(x - 1, y + 1);
      const int g23 = 12* i.get(x    , y + 1);
      const int g33 = 9 * i.get(x + 1, y + 1);
      const int g43 = 4 * i.get(x + 2, y + 1);

      const int g04 = 2 * i.get(x - 2, y + 2);
      const int g14 = 4 * i.get(x - 1, y + 2);
      const int g24 = 5 * i.get(x    , y + 2);
      const int g34 = 4 * i.get(x + 1, y + 2);
      const int g44 = 2 * i.get(x + 2, y + 2);

      // casts are just for verbosity
      out.get(x,y) =
	static_cast<unsigned char>(
	  static_cast<float>(
	    g00 + g10 + g20 + g30 + g40 +
	    g01 + g11 + g21 + g31 + g41 +
	    g02 + g12 + g22 + g32 + g42 +
	    g03 + g13 + g23 + g33 + g43 +
	    g04 + g14 + g24 + g34 + g44) / 159.0f);
    }

  // easiest implementation: borders stays the same
  // todo: blur the borders too

  for(int x = 0; x < i.width(); ++x)
  {
    out.get(x, 0) = i.get(x, 0);
    out.get(x, 1) = i.get(x, 1);
    out.get(x, i.height() - 1) = i.get(x, i.height() - 1);
    out.get(x, i.height() - 2) = i.get(x, i.height() - 2);
  }
  
  for(int y = 0; y < i.width(); ++y)
  {
    out.get(0, y) = i.get(0, y);
    out.get(1, y) = i.get(1, y);
    out.get(i.width() - 1, y) = i.get(i.width() - 1, y);
    out.get(i.width() - 2, y) = i.get(i.width() - 2, y);
  }
  
  return out;
}

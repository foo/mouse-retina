#include "sobel.hpp"

image sobel(const image& i)
{
  image out;
  out.allocate(i.width(), i.height());

  for(int x = 1; x < i.width() - 1; ++x)
    for(int y = 1; y < i.height() - 1; ++y)
    {
      const int vertical =
	-   i.get(x - 1, y - 1)
	- 2*i.get(x,     y - 1)
	-   i.get(x + 1, y - 1)
	+   i.get(x - 1, y + 1)
	+ 2*i.get(x,     y + 1)
	+   i.get(x + 1, y + 1);

      const int horizontal =
	-   i.get(x - 1, y - 1)
	- 2*i.get(x - 1, y)
	-   i.get(x - 1, y + 1)
	+   i.get(x + 1, y - 1)
	+ 2*i.get(x + 1, y)
	+   i.get(x + 1, y + 1);
      
      out.get(x,y) = static_cast<char>(
	sqrtf(vertical*vertical + horizontal*horizontal));
    }
    
  // easiest implementation: borders are zeroed
  // todo: partial gradient
  
  for(int x = 0; x < i.width(); ++x)
  {
    out.get(x, 0) = 0;
    out.get(x, i.height() - 1) = 0;
  }
  
  for(int y = 0; y < i.width(); ++y)
  {
    out.get(0, y) = 0;
    out.get(i.width() - 1, y) = 0;
  }
  
  return out;
}

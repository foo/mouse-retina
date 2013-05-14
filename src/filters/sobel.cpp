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
    
  return out;
}

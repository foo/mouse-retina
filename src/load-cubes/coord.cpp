#include "coord.hpp"

bool coord::operator<(const coord& c) const
{
  // Lexicographical order. Most significant coordinate is z.
  
  if(z < c.z)
    return true;
  else if (c.z < z)
    return false;
  else //if(x == c.x)
  {
    if(y < c.y)
      return true;
    else if (c.y < y)
      return false;
    else //if(y == c.y)
    {
      return x < c.x;
    }
  }
}

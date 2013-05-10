#include "coord.hpp"

bool coord::operator<(const coord& c) const
{
  if(x < c.x)
    return true;
  else if (c.x < x)
    return false;
  else //if(x == c.x)
  {
    if(y < c.y)
      return true;
    else if (c.y < y)
      return false;
    else //if(y == c.y)
    {
      return z < c.z;
    }
  }
}

#pragma once

struct coord
{
  int x, y, z;
  coord(int X = -1, int Y = -1, int Z = -1)
    : x(X), y(Y), z(Z) {}
  bool operator<(const coord& c) const;
};



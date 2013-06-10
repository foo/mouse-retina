#pragma once

#include <vector>

struct union_find
{
private:
  std::vector<int> p;
public:
  int Find(int x);
  bool Union(int x, int y);
  bool OwnRank(int x) const;
  int Parent(int x) const;
  union_find(int sz);
};

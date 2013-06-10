#include "unionfind.hpp"

int union_find::Find(int x)
{
  if(p[x] == x) return x;
  p[x] = Find(p[x]);
  return p[x];
}

bool union_find::Union(int x, int y)
{
  if(Find(x) == Find(y)) return false;
  p[p[x]] = p[y];
  return true;
}

bool union_find::OwnRank(int x) const
{
  return p[x] == x;
}

int union_find::Parent(int x) const
{
  return p[x];
}

union_find::union_find(int sz)
{
  p.resize(sz);
  for(int i = 0; i < sz; i++) p[i] = i;
}

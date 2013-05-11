#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <cassert>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

class cube
{
public:
  static const int dim = 128;
  cube(const boost::filesystem::path& path);
  unsigned char& voxel(int x, int y, int z);
  unsigned char voxel(int x, int y, int z) const;
private:
  std::vector<unsigned char> data;
public:
  const std::vector<unsigned char>& get_data() const { return data; }
};


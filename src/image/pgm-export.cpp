#include "pgm-export.hpp"

void pgm_export(const image& i, const boost::filesystem::path& path)
{
  boost::filesystem::ofstream pgm(path);

  pgm << "P2\n"
      << i.width << ' ' << i.height << '\n'
      << 255 << '\n';

  for(int y = 0; y < i.height; ++y)
  {
    for(int x = 0; x < i.width; ++x)
      pgm << static_cast<int>(i.get(x, y)) << ' ';
    pgm << '\n';
  }
}

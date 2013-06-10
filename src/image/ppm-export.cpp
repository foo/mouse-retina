#include "ppm-export.hpp"

void ppm_export(const rgb_image& i, const boost::filesystem::path& path)
{
  ppm_export(std::get<0>(i), std::get<1>(i), std::get<2>(i), path);
}

void ppm_export(const image& r, const image& g, const image& b, const boost::filesystem::path& path)
{
  if(exists(path))
  {
    std::cerr << "Error exporting to PPM! File "
	      << path << " already exists." << std::endl;
    exit(1);
  }

  boost::filesystem::ofstream ppm(path);

  ppm << "P3\n"
      << r.width() << ' ' << r.height() << '\n'
      << 255 << '\n';

  for(int y = 0; y < r.height(); ++y)
  {
    for(int x = 0; x < r.width(); ++x){
      ppm << static_cast<int>(r.pixel(x, y)) << ' ';
      ppm << static_cast<int>(g.pixel(x, y)) << ' ';
      ppm << static_cast<int>(b.pixel(x, y)) << ' ';
    }
    ppm << '\n';
  }
}

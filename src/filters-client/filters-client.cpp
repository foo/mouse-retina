#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "../load-cubes/grid.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"
#include "../image/from-grid.hpp"

#include "../filters/sobel.hpp"
#include "../filters/gaussian.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  dataset d(dataset_dir);
  grid g(d);

  std::cerr << "Obtaining image from grid." << std::endl;
  image i = from_grid(g, 10, 300, 10, 300, 100);

  std::cerr
    << "Exporting original image to output/filters/original.pgm."
    << std::endl;
  
  pgm_export(i, boost::filesystem::path(
      "../output/filters/original.pgm"));

  std::cerr
    << "Applying gaussian filter."
    << std::endl;
  
  image i_gaussian = gaussian(i);
  
  std::cerr
    << "Exporting image to output/filters/gaussian.pgm."
    << std::endl;
  
  pgm_export(i_gaussian, boost::filesystem::path(
      "../output/filters/gaussian.pgm"));
  
  std::cerr
    << "Applying sobel filter."
    << std::endl;
  
  image i_sobel = sobel(i);

  std::cerr
    << "Exporting image to output/filters/sobel.pgm."
    << std::endl;
  
  pgm_export(i_sobel, boost::filesystem::path(
      "../output/filters/sobel.pgm"));

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

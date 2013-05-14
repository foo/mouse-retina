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
#include "../filters/sharpen.hpp"
#include "../filters/threshold.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  dataset d(dataset_dir);
  grid g(d);

  std::cerr << "Obtaining image from grid." << std::endl;
  image i = from_grid(g, 10, 300, 10, 300, 100);

  {
    std::cerr
      << "Exporting original image to output/filters/original.pgm."
      << std::endl;
  
    pgm_export(i, boost::filesystem::path(
	"../output/filters/original.pgm"));
  }

  {
    std::cerr
      << "Applying gaussian filter."
      << std::endl;
  
    image i_gaussian = gaussian5x5(i);
  
    std::cerr
      << "Exporting image to output/filters/gaussian.pgm."
      << std::endl;
  
    pgm_export(i_gaussian, boost::filesystem::path(
	"../output/filters/gaussian.pgm"));
  }

  {
    std::cerr
      << "Applying sharpening filter."
      << std::endl;
  
    image i_sharpen = sharpen(i);
  
    std::cerr
      << "Exporting image to output/filters/sharpen.pgm."
      << std::endl;
  
    pgm_export(i_sharpen, boost::filesystem::path(
	"../output/filters/sharpen.pgm"));
  }

  {
    std::cerr
      << "Applying sobel filter."
      << std::endl;
  
    image i_sobel = sobel(i);

    std::cerr
      << "Exporting image to output/filters/sobel.pgm."
      << std::endl;
  
    pgm_export(i_sobel, boost::filesystem::path(
	"../output/filters/sobel.pgm"));
  }

  {
    std::cerr
      << "Applying all filters (edge detection)."
      << std::endl;

    image i_gaussian = gaussian5x5(i);
    image i_gaussian_sharpened = sharpen(i_gaussian);
    image i_edge_detection = sobel(i_gaussian_sharpened);
  
    std::cerr
      << "Exporting image to output/filters/edge-detection.pgm."
      << std::endl;
  
    pgm_export(i_edge_detection, boost::filesystem::path(
	"../output/filters/edge-detection.pgm"));
  }

  {
    std::cerr
      << "Applying all filters with thresholding (edge detection)."
      << std::endl;

    image i_gaussian = gaussian5x5(i);
    image i_gaussian_sharpened = sharpen(i_gaussian);
    image i_sobel = sobel(i_gaussian_sharpened);
    image i_edge_detection = threshold(i_sobel, 130);
  
    std::cerr
      << "Exporting image to output/filters/edge-detection-threshold.pgm."
      << std::endl;
  
    pgm_export(i_edge_detection, boost::filesystem::path(
	"../output/filters/edge-detection-threshold.pgm"));
  }

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

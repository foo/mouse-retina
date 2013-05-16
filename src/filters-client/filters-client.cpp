#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "../load-cubes/grid.hpp"
#include "../load-cubes/cross-section.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"

#include "../filters/sobel.hpp"
#include "../filters/gaussian.hpp"
#include "../filters/sharpen.hpp"
#include "../filters/threshold.hpp"
#include "../filters/dilation.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  dataset_files d(dataset_dir);
  grid g(d);

  std::cerr << "Obtaining image from grid." << std::endl;
  image i = cross_section(g, 10, 300, 10, 300, 100);

  {
    std::cerr
      << "Exporting original image to output/filters/original.pgm."
      << std::endl;
  
    pgm_export(i, boost::filesystem::path(
	"../output/filters/original.pgm"));
  }

  {
    std::cerr
      << "Edge detection."
      << std::endl;

    for(int threshold_value = 130; threshold_value <= 180; threshold_value += 10)
    {
      image i_edge_detection =
	  threshold(
	    sobel(
	      sharpen(
		gaussian5x5(i))),
	    threshold_value);
  
      image i_edge_detection_with_dilation =
	  erosion(
	    dilation(
	      threshold(
		sobel(
		  sharpen(
		    gaussian5x5(i))),
		threshold_value)));

      {
	std::stringstream ss;
	ss << "../output/filters/edge_detection" << threshold_value << ".pgm";
      
	std::cerr	<< "Exporting image to " << ss.str() << std::endl;
	pgm_export(i_edge_detection, boost::filesystem::path(ss.str()));
      }
      {
	std::stringstream ss;
	ss << "../output/filters/edge_detection_minkowski" << threshold_value << ".pgm";
      
	std::cerr	<< "Exporting image to " << ss.str() << std::endl;
	pgm_export(i_edge_detection_with_dilation, boost::filesystem::path(ss.str()));
      }
    }
  }

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

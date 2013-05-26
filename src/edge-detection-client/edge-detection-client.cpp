#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "../dataset/dataset.hpp"
#include "../dataset/cross-section.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"

#include "../filters/sobel.hpp"
#include "../filters/gaussian.hpp"
#include "../filters/sharpen.hpp"
#include "../filters/threshold.hpp"
#include "../filters/dilation.hpp"
#include "../edge-detection/gradient.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  dataset d(dataset_dir);

  std::cerr << "Obtaining image from grid." << std::endl;
  //image i = cross_section(d, 10, 300, 10, 300, 100);
  image i = cross_section_z(d, 50, 320, 50, 320, 120);
	
  {
    std::cerr
      << "Exporting original image to output/edge-detection/original.pgm."
      << std::endl;
  
    pgm_export(i, boost::filesystem::path(
	"../output/edge-detection/original.pgm"));
	
    pgm_export(sharpen(i), boost::filesystem::path(
	"../output/edge-detection/original_gauss.pgm"));
  }

  {
    std::cerr
      << "Edge detection."
      << std::endl;
	for(int supp_radius = 1; supp_radius <= 1; supp_radius++)
    for(int thigh = 190; thigh <= 220; thigh += 100)
    for(int which = 0; which < 20; which+=1)
    for(int tlow = 40; tlow < thigh; tlow += 1000)
    {
      image i_edge_detection =
      gradient(
			//sobel(
			  sharpen(
			gaussian5x5(i)),
		 thigh, tlow, supp_radius, which);
  		/*
      image i_edge_detection_with_dilation =
      gradient(
		  erosion(
			dilation(
			sobel(
			  sharpen(
				gaussian5x5(i))))), threshold_value);
		*/
      {
	std::stringstream ss;
	ss << "../output/edge-detection/edge_detection" << thigh << "_"<< tlow << "_" << supp_radius<<"_" << which <<".pgm";
      
	std::cerr	<< "Exporting image to " << ss.str() << std::endl;
	pgm_export(i_edge_detection, boost::filesystem::path(ss.str()));
      }/*
      {
	std::stringstream ss;
	ss << "../output/edge-detection/edge_detection_minkowski" << threshold_value << ".pgm";
      
	std::cerr	<< "Exporting image to " << ss.str() << std::endl;
	pgm_export(i_edge_detection_with_dilation, boost::filesystem::path(ss.str()));
      }*/
    }
  }

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

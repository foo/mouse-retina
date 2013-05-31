#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "../dataset/dataset.hpp"
#include "../dataset/cross-section.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"

#include "../filters/sobel.hpp"
#include "../filters/gaussian.hpp"
#include "../filters/sharpen.hpp"
#include "../filters/threshold.hpp"
#include "../filters/dilation.hpp"
#include "../config/options.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char* argv[])
{
  po::options_description opt_desc("Filters client presents effects of some filters, like sobel, erosion, dilation etc.");

  opt_desc.add_options()
    ("dataset-path,d",
      po::value<std::string>()->default_value("../images/e1088_mag1_small"),
      "Specify path to dataset in Knossos format.")
    ("cross-section-x1",
      po::value<int>()->default_value(0),
     "Cross section dimensions. X coordinate of top-left corner.")
    ("cross-section-y1",
      po::value<int>()->default_value(0),
     "Cross section dimensions. Y coordinate of top-left corner.")
    ("cross-section-x2",
      po::value<int>()->default_value(128),
     "Cross section dimensions. X coordinate of bottom-right corner.")
    ("cross-section-y2",
      po::value<int>()->default_value(128),
     "Cross section dimensions. Y coordinate of bottom-right corner.")
    ("cross-section-z",
      po::value<int>()->default_value(40),
     "Cross section dimensions. Z coordinate of cross-section plane.")
    ("threshold-begin",
      po::value<int>()->default_value(120),
     "Initial value of threshold in loop.")
    ("threshold-end",
      po::value<int>()->default_value(140),
     "Limit value of threshold in loop.")
    ("threshold-step",
      po::value<int>()->default_value(2),
     "Step value of threshold in loop.")
     ("out-dir",
      po::value<std::string>()->default_value("../output/filters-client"),
       "Output directory.")
    ("out-filename",
      po::value<std::string>()->default_value("filter"),
     "Prefix of output filename.");
  
  options opts(opt_desc, argc, argv);
    
  dataset d(opts.string_var("dataset-path"));

  std::cerr << "Obtaining image from grid." << std::endl;
  image i = cross_section_z(d,
    opts.int_var("cross-section-x1"),
    opts.int_var("cross-section-x2"),
    opts.int_var("cross-section-y1"),
    opts.int_var("cross-section-y2"),
    opts.int_var("cross-section-z"));

  {
    fs::path p = fs::path() / opts.string_var("out-dir") / "original.pgm";

    std::cerr
      << "Exporting original image to " << p << "."
      << std::endl;
  
    pgm_export(i, p);
  }

  {
    for(int threshold_value = opts.int_var("threshold-begin");
	threshold_value <= opts.int_var("threshold-end");
	threshold_value += opts.int_var("threshold-step"))
    {
      image i_edge_detection =
	  erosion(
	    dilation(
	      threshold(
		sobel(
		  sharpen(
		    gaussian5x5(i))),
		threshold_value)));

      {
	std::stringstream filename;
	filename << opts.string_var("out-filename")
		 << threshold_value << ".pgm";
	
      	fs::path p = fs::path() / opts.string_var("out-dir") / filename.str();

	std::cerr << "Exporting image to " << p << std::endl;
	pgm_export(i_edge_detection, p);
      }
    }
  }

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

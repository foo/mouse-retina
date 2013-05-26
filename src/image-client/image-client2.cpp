#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "../dataset/dataset.hpp"
#include "../dataset/cross-section.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"
#include "../config/options.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
  po::options_description opt_desc("Image client reads cubes from dataset, and renders serie of arbitrary slice images.");

  opt_desc.add_options()
    ("dataset-path,d",
      po::value<std::string>()->default_value("../images/e1088_mag1_small"),
      "Specify path to dataset in Knossos format.")
    ("width,w",
      po::value<int>()->default_value(100),
     "Width of the image")
    ("height,h",
      po::value<int>()->default_value(100),
     "Height of the image")
    ("left_down_corner_x",
      po::value<float>()->default_value(100),
     "")
    ("left_down_corner_y",
      po::value<float>()->default_value(100),
     "")
    ("left_down_corner_z",
      po::value<float>()->default_value(100),
     "")
    ("w_vec_x",
      po::value<float>()->default_value(100),
     "")
    ("w_vec_y",
      po::value<float>()->default_value(100),
     "")
    ("w_vec_z",
      po::value<float>()->default_value(100),
     "")
    ("h_vec_x",
      po::value<float>()->default_value(100),
     "")
    ("h_vec_y",
      po::value<float>()->default_value(100),
     "")
    ("h_vec_z",
      po::value<float>()->default_value(100),
     "")
    ("out-dir",
      po::value<std::string>()->default_value("../output/image-client"),
     "Output directory.")
    ("out-filename",
      po::value<std::string>()->default_value("arbitrary-slice.pgm"),
     "Output file name.");

  options opts(opt_desc, argc, argv);
  
  dataset d(opts.string_var("dataset-path"));

  image i = cross_section_arbitrary(d,
				    opts.int_var("width"),
				    opts.int_var("height"),
				    opts.float_var("left_down_corner_x"),
				    opts.float_var("left_down_corner_y"),
				    opts.float_var("left_down_corner_z"),
				    opts.float_var("w_vec_x"),
				    opts.float_var("w_vec_y"),
				    opts.float_var("w_vec_z"),
				    opts.float_var("h_vec_x"),
				    opts.float_var("h_vec_y"),
				    opts.float_var("h_vec_z"));
  std::cout << "Successfully loaded image from grid" << std::endl;

  std::stringstream ss;
  ss << opts.string_var("out-dir") << "/"
     << opts.string_var("out-filename");
    
  pgm_export(i,
	     boost::filesystem::path(ss.str()));
  std::cout << "Successfully exported slice of tissue to file "
	    << ss.str() << "." << std::endl;

  return 0;
}

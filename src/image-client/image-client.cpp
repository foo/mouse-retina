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
  po::options_description opt_desc("Image client reads cubes from dataset, and renders serie of images through the dataset.");

  opt_desc.add_options()
    ("dataset-path,d",
      po::value<std::string>()->default_value("../images/e1088_mag1_small"),
      "Specify path to dataset in Knossos format.")
    ("z-begin",
      po::value<int>()->default_value(0),
     "Loop through dataset z coordinate; initial value")
    ("z-end",
      po::value<int>()->default_value(10),
     "Loop through dataset z coordinate; limit value")
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
    ("out-dir",
      po::value<std::string>()->default_value("../output/image-client"),
     "Output directory.")
    ("out-filename",
      po::value<std::string>()->default_value("slice"),
     "Prefix of output filename. E.g. for out-filname=slice, the program will output slice1.pgm, slice2.pgm etc.");

  options opts(opt_desc, argc, argv);
  
  dataset d(opts.string_var("dataset-path"));

  for(int z = opts.int_var("z-begin");
      z < opts.int_var("z-end");
      z ++)
  {
    /*if(z % cube::dim == 0)
    {
      const int useless_z = (z / cube::dim) - 1;

      d.unload_z_lower_than(d.min_z + useless_z);
    }*/
    
    std::cout << "Processing z coordinate " << z << std::endl;
    image i = cross_section_z(d,
      opts.int_var("cross-section-x1"),
      opts.int_var("cross-section-x2"),
      opts.int_var("cross-section-y1"),
      opts.int_var("cross-section-y2"),
      z);
    std::cout << "Successfully loaded image from grid" << std::endl;

    std::stringstream ss;
    ss << opts.string_var("out-dir") << "/"
       << opts.string_var("out-filename") << z << ".pgm";
    
    pgm_export(i,
      boost::filesystem::path(ss.str()));
    std::cout << "Successfully exported slice of tissue to file "
	      << ss.str() << "." << std::endl;
  }
  return 0;
}

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
#include "../config/options.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
  po::options_description opt_desc("Edge detection client. Available options");

  opt_desc.add_options()
    ("dataset-path,d",
     po::value<std::string>()->default_value("../images/e1088_mag1_small"),
     "Specify path to dataset in Knossos format.")
    ("cross-section-x1",
     po::value<int>()->default_value(50),
     "Cross section dimensions. X coordinate of top-left corner.")
    ("cross-section-y1",
     po::value<int>()->default_value(50),
     "Cross section dimensions. Y coordinate of top-left corner.")
    ("cross-section-x2",
     po::value<int>()->default_value(320),
     "Cross section dimensions. X coordinate of bottom-right corner.")
    ("cross-section-y2",
     po::value<int>()->default_value(320),
     "Cross section dimensions. Y coordinate of bottom-right corner.")
    ("cross-section-z",
     po::value<int>()->default_value(120),
     "Cross section dimensions. Z coordinate of cross-section plane.")
    ("sup_rad1", po::value<int>(), "")
    ("sup_rad2", po::value<int>(), "")
    ("thresh_high1", po::value<int>(), "")
    ("thresh_high2", po::value<int>(), "")
    ("thresh_diff1", po::value<int>(), "")
    ("thresh_diff2", po::value<int>(), "");

  options opts(opt_desc, argc, argv);

  dataset d(opts.string_var("dataset-path"));

  image i = cross_section_z(d,
                            opts.int_var("cross-section-x1"),
                            opts.int_var("cross-section-x2"),
                            opts.int_var("cross-section-y1"),
                            opts.int_var("cross-section-y2"),
                            opts.int_var("cross-section-z"));


  gaussian(i,0.8408964);

  {
    std::cerr
      << "Exporting original image to output/edge-detection/original.pgm."
      << std::endl;

    pgm_export(i, boost::filesystem::path("../output/edge-detection/original.pgm"));

    pgm_export(sharpen(i), boost::filesystem::path("../output/edge-detection/original_gauss.pgm"));
  }

  {
    int sup_rad1 = opts.int_var("sup_rad1");
    int sup_rad2 = opts.int_var("sup_rad2");
    int thresh_high1 = opts.int_var("thresh_high1");
    int thresh_high2 = opts.int_var("thresh_high2");
    int thresh_diff1 = opts.int_var("thresh_diff1");
    int thresh_diff2 = opts.int_var("thresh_diff2");
    for(int supp_radius = sup_rad1; supp_radius <= sup_rad2; supp_radius++)
      for(int thigh = thresh_high1; thigh <= thresh_high2; thigh += 10)
        for(int tlow = thigh-thresh_diff1; tlow <= thigh-thresh_diff2; tlow += 10)
          {
            image i_edge_detection =
              gradient(i,thigh,tlow,supp_radius,0);

            {
              std::stringstream ss;
              ss << "../output/edge-detection/edge_detection" << thigh << "_"<< tlow << "_" << supp_radius<<"_" << 0 <<".pgm";

              std::cerr << "Exporting image to " << ss.str() << std::endl;
              pgm_export(i_edge_detection, boost::filesystem::path(ss.str()));
            }
          }
  }

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

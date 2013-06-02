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
    ("gaussian_sigma", po::value<float>()->default_value(0.8408964), "")
    ("sup_rad1", po::value<int>(), "")
    ("sup_rad2", po::value<int>(), "")
    ("thresh_high1", po::value<int>(), "")
    ("thresh_high2", po::value<int>(), "")
    ("thresh_diff1", po::value<int>(), "")
    ("thresh_diff2", po::value<int>(), "")
    ("ep1", po::value<float>(), "")
    ("ep2", po::value<float>(), "")
    ("ep3", po::value<float>(), "")
    ("thresh_ray", po::value<int>(), "")
    ("union_ray", po::value<int>(), "")
    ("print_color", po::value<bool>(), "")
    ("do_matching", po::value<bool>(), "")
    ;

  options opts(opt_desc, argc, argv);

  dataset d(opts.string_var("dataset-path"));

  image i = cross_section_z(d,
                            opts.int_var("cross-section-x1"),
                            opts.int_var("cross-section-x2"),
                            opts.int_var("cross-section-y1"),
                            opts.int_var("cross-section-y2"),
                            opts.int_var("cross-section-z"));

  {
    std::cerr
      << "Exporting original image to output/edge-detection/original.pgm."
      << std::endl;

    pgm_export(i, boost::filesystem::path("../output/edge-detection/original.pgm"));
  }

  image magnified = gaussian(i, opts.float_var("gaussian_sigma"));

  {
    std::cerr
      << "Exporting magnified image to output/edge-detection/magnified.pgm."
      << std::endl;

    pgm_export(magnified, boost::filesystem::path("../output/edge-detection/magnified.pgm"));
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
            image i_edge_detection;
	    rgb_image i_before_join;
	    rgb_image i_after_join;
	    std::tie(i_edge_detection, i_before_join, i_after_join)
	      = detect_edges(magnified,thigh,tlow,supp_radius,0,
		       opts.float_var("ep1"),
		       opts.float_var("ep2"),
		       opts.float_var("ep3"),
		       opts.bool_var("print_color"),
		       opts.bool_var("do_matching"),
		       opts.int_var("union_ray"),
		       opts.int_var("thresh_ray")
		       );
	    {
              std::stringstream ss;
              ss << "../output/edge-detection/edge_detection" << thigh << "_"<< tlow << "_" << supp_radius << ".pgm";

              std::cerr << "Exporting image to " << ss.str() << std::endl;
              pgm_export(i_edge_detection, boost::filesystem::path(ss.str()));
            }

            {
              std::stringstream ss;
              ss << "../output/edge-detection/edge_detection" << thigh << "_"<< tlow << "_" << supp_radius << "before.pgm";

              std::cerr << "Exporting image to " << ss.str() << std::endl;
              ppm_export(i_before_join, boost::filesystem::path(ss.str()));
            }
	    
	    {
              std::stringstream ss;
              ss << "../output/edge-detection/edge_detection" << thigh << "_"<< tlow << "_" << supp_radius << "after.pgm";

              std::cerr << "Exporting image to " << ss.str() << std::endl;
              ppm_export(i_after_join, boost::filesystem::path(ss.str()));
            }
          }
    
  }

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

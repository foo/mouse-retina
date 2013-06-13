#pragma once

#include "../image/image.hpp"
#include "../image/ppm-export.hpp"
#include "../image/pgm-export.hpp"
#include "../filters/gaussian.hpp"
#include "../filters/sharpen.hpp"
#include "../utils/unionfind.hpp"

#include "../filters/sobel.hpp"
#include "compound.hpp"
#include "matcher.hpp"
#include "gradient.hpp"

#include <cmath>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <tuple>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/path_traits.hpp>
#include <iostream>
#include <cassert>
#include <sstream>
#include <tuple>

std::tuple<image, rgb_image, rgb_image>
detect_edges(const image& i, int high_threshold, int low_threshold, int supp_radius, int kto,
             float ep1, float ep2, float ep3, bool print_compounds, bool do_matching,
             int union_ray, int thresh_ray, std::string slice_coords);

void print_compounds_to_file(std::vector<Compound>compound, 
							 const boost::filesystem::path& path);

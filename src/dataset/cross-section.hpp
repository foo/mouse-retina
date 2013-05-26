#pragma once

#include <algorithm>

#include "dataset.hpp"
#include "cube.hpp"
#include "../image/image.hpp"

// x, y, z are voxel numbers
image cross_section_z(dataset& d, int x1, int x2, int y1, int y2, int z);
image cross_section_arbitrary(
			      dataset& d, int w, int h,
			      float left_down_corner_x,
			      float left_down_corner_y,
			      float left_down_corner_z,
			      float w_vec_x,
			      float w_vec_y,
			      float w_vec_z,
			      float h_vec_x,
			      float h_vec_y,
			      float h_vec_z);

#pragma once

#include <algorithm>

#include "grid.hpp"
#include "cube.hpp"
#include "../image/image.hpp"

// x, y, z are voxel numbers
image cross_section(grid& g, int x1, int x2, int y1, int y2, int z);
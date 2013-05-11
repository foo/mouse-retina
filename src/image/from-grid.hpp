#pragma once

#include "image.hpp"
#include "../load-cubes/grid.hpp"
#include "../load-cubes/cube.hpp"

// x, y, z are voxel numbers
image from_grid(grid& g, int x1, int x2, int y1, int y2, int z);

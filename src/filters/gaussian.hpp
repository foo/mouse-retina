#pragma once

#include "../image/image.hpp"
#include "box.hpp"
#include <cmath>

#define PI (2*acos(0))
image gaussian(const image& i, double sigma);
image gaussian5x5(const image& i);

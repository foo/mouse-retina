#pragma once

#include <cmath>

#include "../image/image.hpp"
#include "box.hpp"

image sobel(const image& i);
std::pair<float, float> sobel_vector(const image& i, int x, int y);

#pragma once

#include "../image/image.hpp"
#include "box.hpp"

void threshold_in_place(image& i, int threshold_value);
image threshold(const image& i, int threshold_value);

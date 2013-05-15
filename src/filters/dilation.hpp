#pragma once

#include <cassert>

#include "box.hpp"
#include "threshold.hpp"
#include "../image/image.hpp"
#include "../image/binary-operations.hpp"

image dilation(const image& i);
image erosion(const image& i);

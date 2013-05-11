#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "image.hpp"

void pgm_export(const image& i, const boost::filesystem::path& path);

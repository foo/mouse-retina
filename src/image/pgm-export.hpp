#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/path_traits.hpp>

#include "image.hpp"

void pgm_export(const image& i, const boost::filesystem::path& path);

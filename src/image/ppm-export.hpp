#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/path_traits.hpp>
#include "image.hpp"

void ppm_export(const image& r, const image& g, const image& b,
	const boost::filesystem::path& path);
void ppm_export(const rgb_image& i, const boost::filesystem::path& path);

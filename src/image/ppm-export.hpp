#pragma once

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "image.hpp"

void ppm_export(const image& r, const image& g, const image& b,
	const boost::filesystem::path& path);

#include "dataset.hpp"

dataset::dataset(const std::string& dataset_dir)
  : ds_files(dataset_dir),
    min_x(ds_files.min_x), max_x(ds_files.max_x),
    min_y(ds_files.min_y), max_y(ds_files.max_y),
    min_z(ds_files.min_z), max_z(ds_files.max_z),
    size_x(ds_files.max_x - ds_files.min_x + 1),
    size_y(ds_files.max_y - ds_files.min_y + 1),
    size_z(ds_files.max_z - ds_files.min_z + 1)
{}

int dataset::cube_cache_size() const
{
  return cube_cache.size();
}

void dataset::unload_from_cache(const coord& c)
{
  cube_cache.erase(cube_cache.find(c));
}

void dataset::unload_z_higher_than(int z_limit)
{
  std::map<coord, cube>::iterator iter_limit;

  const coord coord_limit(INT_MAX, INT_MAX, z_limit);
  
  iter_limit = cube_cache.upper_bound(coord_limit);
  cube_cache.erase(iter_limit, cube_cache.end());
}

void dataset::unload_z_lower_than(int z_limit)
{
  std::map<coord, cube>::iterator iter_limit;

  const coord coord_limit(0, 0, z_limit);
  
  iter_limit = cube_cache.lower_bound(coord_limit);
  cube_cache.erase(cube_cache.begin(), iter_limit);
}

const cube& dataset::get_cube(const coord& c)
{
  std::map<coord, cube>::iterator search_for_cube;
  search_for_cube = cube_cache.find(c);

  if(search_for_cube != cube_cache.end())
  {
    return search_for_cube->second;
  }
  else
  {
    // load cube from disk to memory

    auto search_for_file = ds_files.cube_files.find(c);

    if(search_for_file != ds_files.cube_files.end())
    {
      cube new_cube(search_for_file->second.string().c_str());
      cube_cache.insert(std::make_pair(c, std::move(new_cube)));
      return cube_cache.find(c)->second; // cannot return new_cube, as it is ripped out of its internals
    }
    else
    {
      std::cerr
	<< "Cube out of dataset. Program tried to cache cube "
	<< c.x << ' ' << c.y << ' ' << c.z << std::endl;
      exit(1);
    }
  }
}

unsigned char dataset::voxel(int x, int y, int z)
{
  const int x_voxel = x % cube::dim;
  const int y_voxel = y % cube::dim;
  const int z_voxel = z % cube::dim;
  
  const int cube_x = min_x + x / cube::dim;
  const int cube_y = min_y + y / cube::dim;
  const int cube_z = min_z + z / cube::dim;
  
  const cube& cube_of_interest = get_cube(cube_x, cube_y, cube_z);

  return cube_of_interest.voxel(x_voxel, y_voxel, z_voxel);
}

float dataset::interpolate_voxel(float x, float y, float z)
{
  // Calculating nearby voxel coordinates
  const int ix = static_cast<int>(x);
  const int iy = static_cast<int>(y);
  const int iz = static_cast<int>(z);

  // Calculating interpolation weights
  const float ax = x - floor(x);
  const float ay = y - floor(y);
  const float az = z - floor(z);

  // Getting colors of surrounding voxels
  const float v_000 = static_cast<float>(voxel(ix    , iy    , iz    ));
  const float v_001 = static_cast<float>(voxel(ix    , iy    , iz + 1));
  const float v_010 = static_cast<float>(voxel(ix    , iy + 1, iz    ));
  const float v_011 = static_cast<float>(voxel(ix    , iy + 1, iz + 1));
  const float v_100 = static_cast<float>(voxel(ix + 1, iy    , iz    ));
  const float v_101 = static_cast<float>(voxel(ix + 1, iy    , iz + 1));
  const float v_110 = static_cast<float>(voxel(ix + 1, iy + 1, iz    ));
  const float v_111 = static_cast<float>(voxel(ix + 1, iy + 1, iz + 1));

  // Interpolation along x coordinate
  const float v_x00 = ax*v_000 + (1.0f - ax)*v_100;
  const float v_x01 = ax*v_001 + (1.0f - ax)*v_101;
  const float v_x10 = ax*v_010 + (1.0f - ax)*v_110;
  const float v_x11 = ax*v_011 + (1.0f - ax)*v_111;

  // Interpolation along y coordinate
  const float v_xy0 = ay*v_x00 + (1.0f - ay)*v_x10;
  const float v_xy1 = ay*v_x01 + (1.0f - ay)*v_x11;

  // Interpolation along z coordinate
  const float v_xyz = az*v_xy0 + (1.0f - az)*v_xy1;
  
  return v_xyz;
}

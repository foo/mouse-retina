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

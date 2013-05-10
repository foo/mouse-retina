#include "dataset.hpp"

dataset::dataset(const char* const dataset_dir)
{
  populate_cube_files(dataset_dir);

  find_min_and_max_coords();

  check_if_dataset_has_holes();
}

void dataset::find_min_and_max_coords()
{
  namespace fs = boost::filesystem;
  min_x = min_y = min_z = INT_MAX;
  max_x = max_y = max_z = INT_MIN;
  
  for(std::map<coord, fs::path>::iterator i = cube_files.begin();
      i != cube_files.end(); ++i)
  {
    if(i->first.x > max_x) max_x = i->first.x;
    if(i->first.x < min_x) min_x = i->first.x;
    if(i->first.y > max_y) max_y = i->first.y;
    if(i->first.y < min_y) min_y = i->first.y;
    if(i->first.z > max_z) max_z = i->first.z;
    if(i->first.z < min_z) min_z = i->first.z;
  }
}

void dataset::check_if_dataset_has_holes()
{
  for(int x = min_x; x <= max_x; ++x)
    for(int y = min_y; y <= max_y; ++y)
      for(int z = min_z; z <= max_z; ++z)
      {
	if(cube_files.find(coord(x, y, z)) == cube_files.end())
	{
	  std::cerr
	    << "Checking if dataset has holes: could not find cube at "
	    << x << ' ' << y << ' ' << z << std::endl;
	  exit(1);
	}
      }
}

void dataset::print_cube_files()
{
  namespace fs = boost::filesystem;
  for(std::map<coord, fs::path>::iterator i = cube_files.begin();
      i != cube_files.end(); ++i)
  {
    std::cerr << i->first.x << " " << i->first.y << " " << i->first.z
	      << ": " << i->second << std::endl;
  }
}

void dataset::populate_cube_files(const char* const dataset_dir)
{
  namespace fs = boost::filesystem;
  fs::path dataset_root(dataset_dir);

  fs::recursive_directory_iterator end;
  fs::recursive_directory_iterator file_itr(dataset_dir);
  for(; file_itr != end; ++file_itr) {
    if(!fs::is_directory(*file_itr) && fs::extension(*file_itr) == ".raw")
    {
      std::string filename = (*file_itr).path().filename().string();

      // let's assume filenames are in following format:
      // <dataset name>_x<4 digits>_y<4 digits>_z<4 digits>.raw

      const int x_pos = filename.size()
	- 4  // extension and dot
	- 4  // z number
	- 2  // "_z"
	- 4  // y number
	- 2  // "_y"
	- 4; // x number
      
      std::istringstream iss(std::string(filename.begin() + x_pos, filename.end()));

      coord c;
      iss >> c.x;
      iss.ignore(1, '_');
      iss.ignore(1, 'y');
      iss >> c.y;
      iss.ignore(1, '_');
      iss.ignore(1, 'z');
      iss >> c.z;

      cube_files.insert(std::make_pair(c, (*file_itr).path()));
    }
  }
}

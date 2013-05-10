#include "dataset.hpp"

dataset::dataset(const char* const dataset_dir)
{
  populate_cube_files(dataset_dir);

  // todo: create a map from coord to files
  // todo: find min and max x,y,z and store in dataset class member
  // todo: check if cube has holes inside
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
      std::cerr << filename << std::endl;

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

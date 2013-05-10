#include "dataset.hpp"

dataset::dataset(const char* const dataset_dir)
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
	- 4 // extension and dot
	- 4 // z number
	- 2 // _z
	- 4 // y number
	- 2 //_y
	- 4; // x number
      
      std::istringstream iss(std::string(filename.begin() + x_pos, filename.end()));

      int x, y, z;
      char c;
      iss >> x >> c >> c >> y >> c >> c >> z;
      std::cerr << x << ' ' << y << ' ' << z << '\n';
    }
  }

  // todo: create a map from coord to files
  // todo: find min and max x,y,z and store in dataset class member
}

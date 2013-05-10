#include "dataset.hpp"

dataset::dataset(const char* const dataset_dir)
{
  namespace fs = boost::filesystem;
  fs::path dataset_root(dataset_dir);

  fs::recursive_directory_iterator end;
  fs::recursive_directory_iterator file_itr(dataset_dir);
  for(; file_itr != end; ++file_itr) {
    if(!fs::is_directory(*file_itr) && fs::extension(*file_itr) == ".raw")
      std::cerr << *file_itr << std::endl;
  }
}

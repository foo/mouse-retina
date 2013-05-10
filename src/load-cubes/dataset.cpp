#include "dataset.hpp"

dataset::dataset(const char* const dataset_dir)
{
  namespace fs = boost::filesystem;
  fs::path dataset_root(dataset_dir);

  fs::recursive_directory_iterator end;
  fs::recursive_directory_iterator dir(dataset_dir);
  for(; dir != end; ++dir) {
    std::cerr << *dir << std::endl;                                    
  }
}

#include "dataset.hpp"

dataset::dataset(const char* const dataset_dir)
{
  namespace fs = boost::filesystem;
  fs::path dataset_root(dataset_dir);
}

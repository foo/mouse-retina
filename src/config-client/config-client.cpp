#include <iostream>
#include <cassert>

#include "../config/knossos-config.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  knossos_config c(dataset_dir);
  c.print_config();

  return 0;
}


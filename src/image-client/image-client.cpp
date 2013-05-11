#include <iostream>
#include <cassert>

#include "../load-cubes/grid.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"

int main(int argc, char* argv[])
{
  image i;
  i.allocate(20, 10);

  for(int x = 5; x < 15; ++x)
    i.get(x, 5) = 0;
  
  pgm_export(i,
      boost::filesystem::path("../output/video/white_rect.pgm"));
  std::cerr << "Successfully wrote white rect." << std::endl;
  return 0;
}

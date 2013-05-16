#include "cross-section.hpp"

/*
  +---------+--------+---------+--------+--------+-------+--------+------+
  |    	    |  	     | 	       |   	|     	 |   	 |     	  |  	 |
  |         |        | 	       |   	|     	 |   	 |     	  |  	 |
  |         |     ---+---------+--------+--------+----	 |     	  |  	 |
  |         |        |         |        |        |   	 |     	  |  	 |
  +---------+--------+---------+--------+--------+-------+--------+------+

  Rectangles symbolizes the grid, vertical line symbolizes selected row.
  2nd cube is left_cube, cubes 3-5 are interior cubes, 6th cube is right_cube.
 */

void copy_row(dataset& g, int x1, int x2, int y, int z,
  std::vector<unsigned char>::iterator& img_iter)
{
  const int z_voxel = z % cube::dim;
  const int y_voxel = y % cube::dim;
  const int x1_voxel = x1 % cube::dim;
  const int x2_voxel = x2 % cube::dim;

  const int left_cube_x = g.min_x + x1 / cube::dim;
  const int right_cube_x = g.min_x + x2 / cube::dim;
  const int cube_y = g.min_y + y / cube::dim;
  const int cube_z = g.min_z + z / cube::dim;

  const cube& left_cube = g.get_cube(left_cube_x, cube_y, cube_z);

  img_iter = std::copy(
    left_cube.voxel_iter(x1_voxel, y_voxel, z_voxel),
    left_cube.voxel_iter(cube::dim, y_voxel, z_voxel),
    img_iter);

  for(int c_x = left_cube_x + 1; c_x < right_cube_x; ++c_x)
  {
    const cube& interior_cube = g.get_cube(c_x, cube_y, cube_z);
    img_iter = std::copy(
      interior_cube.voxel_iter(0, y_voxel, z_voxel),
      interior_cube.voxel_iter(cube::dim, y_voxel, z_voxel),
      img_iter);
  }
  
  const cube& right_cube = g.get_cube(right_cube_x, cube_y, cube_z);

  img_iter = std::copy(
    right_cube.voxel_iter(0, y_voxel, z_voxel),
    right_cube.voxel_iter(x2_voxel, y_voxel, z_voxel),
    img_iter);
}

image cross_section(dataset& g, int x1, int x2, int y1, int y2, int z)
{
  assert(x1 >= 0);
  assert(y1 >= 0);
  assert(z  >= 0);

  assert(x1 <= x2);
  assert(y1 <= y2);

  assert(x2 < g.size_x * cube::dim);
  assert(y2 < g.size_y * cube::dim);
  assert(z  < g.size_z * cube::dim);

  image i;
  i.allocate(x2 - x1, y2 - y1 + 1);

  std::vector<unsigned char>::iterator img_iter;
  img_iter = i.data.begin();

  for(int y = y1; y <= y2; ++y)
  {
    copy_row(g, x1, x2, y, z, img_iter);

    // make sure that exactly one row was processed by copy_row
    assert(img_iter == i.data.begin() + (y - y1 + 1) * i.width());
  }

  return i;
}

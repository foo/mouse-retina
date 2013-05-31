#include "image.hpp"

image::image()
  : w(-1), h(-1)
{
  
}

image::image(const image& i)
  : w(i.w), h(i.h), data(i.data)
{

}

image image::twice_larger(){
	image j;
	j.allocate(width()*2, height()*2);
	for(int x = 0; x < width(); x++)
		for(int y = 0; y < height(); y++){
			int v = pixel(x,y);
			j.pixel(2*x,2*y) = v;
			j.pixel(2*x+1,2*y) = v;
			j.pixel(2*x,2*y+1) = v;
			j.pixel(2*x+1,2*y+1) = v;
		}
	
	return j;
}

image image::twice_smaller(){
	image j;
	j.allocate(width()/2, height()/2);
	for(int x = 0; x < j.width(); x++)
		for(int y = 0; y < j.height(); y++){
			j.pixel(x,y) = (pixel(2*x,2*y) + pixel(2*x+1,2*y) 
						  + pixel(2*x,2*y+1) + pixel(2*x+1,2*y+1))/4;
		}
	
	return j;
}


void image::allocate(int width, int height)
{
  assert(width > 0);
  assert(height > 0);
  assert(!initialized());
  
  w = width;
  h = height;

  data.reserve(w * h);
  std::fill_n(
    std::back_inserter(data),
    w * h,
    static_cast<unsigned char>(255));
}

unsigned char& image::pixel(int x, int y)
{
  assert(is_inside(x, y));
  return data[x + w*y];
}

unsigned char image::pixel(int x, int y) const
{
  assert(is_inside(x, y));
  return data[x + w*y];
}

bool image::is_inside(int x, int y) const
{
  return x >= 0 && y >= 0 && x < w && y < h;
}

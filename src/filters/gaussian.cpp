#include "gaussian.hpp"

image gaussian(const image &i, double sigma){
	int n = (int)(6*sigma+0.9);
	double skw = sigma * sigma;
	if(n%2==0) n--;
	std::vector<int>t;
	int m = n/2;
	t.resize(n*n);
	for(int x = -m; x <= m; x++){
		for(int y = -m; y <= m; y++){
			t[(x+m)*n+y+m] = (int)(10000 * 1./sqrt(2*PI*skw) * exp(-(x*x+y*y)/2./skw));
		}
	}
	box_filter gaussian(t);
	return gaussian.apply_naive(i);
}

image gaussian5x5(const image& i)
{
  // delta is 1.4
  box_filter gaussian(
    {   2,  4,  5,  4,  2,
	4,  9, 12,  9,  4,
	5, 12, 15, 12,  5,
	4,  9, 12,  9,  4,
	2,  4,  5,  4,  2  });

  return gaussian.apply_naive(i);
}

#pragma once

#include <cmath>
#include <stack>
#include <algorithm>
#include <cstdio>

#include "../image/image.hpp"
#define EPS 0.0000001
#define iszero(x) ((x) < EPS && (x) > -EPS)
#define PI (2*acos(0))

class Gradient{
	int x, y; 
	double angle, mag;
	Gradient(int x_, int y_, double ang_, double mag_);
};

//vector<Gradient> gradient(const image& i);
image gradient(const image& i, int high_threshold, int low_threshold, int supp_radius, int kto);
double angle_from_two(double x, double y);

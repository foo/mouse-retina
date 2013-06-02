#pragma once

#include <cmath>
#include <stack>
#include <algorithm>
#include <cstdio>

#include "../image/image.hpp"
#include "../filters/sobel.hpp"
#include "detector.hpp"
#include "matcher.hpp"

#define EPS 0.0000001
#define iszero(x) ((x) < EPS && (x) > -EPS)
#define PI (2*acos(0))

class Gradient{
  int x, y;
  double angle, mag;
  Gradient(int x_, int y_, double ang_, double mag_);
};

image gradient(const image& i, int high_threshold, int low_threshold, int supp_radius, int kto,
               float ep1, float ep2, float ep3, float sigma, bool print_color, bool do_matching,
               int union_ray, int thresh_ray);
double angle_from_two(double x, double y);
void print_compounds(std::vector<Compound>&compounds,int mode, char *path, image &r, image &g, image &b,int*compM);

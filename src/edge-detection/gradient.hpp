#pragma once

#include <cmath>
#include <stack>
#include <algorithm>
#include <cstdio>

#include "../image/image.hpp"
#include "detector.hpp"
#include "matcher.hpp"

#define EPS 0.0000001
#define iszero(x) ((x) < EPS && (x) > -EPS)
#define PI (2*acos(0))

class Gradient{
	int x, y, n, m, R; 
	double angle;
	double ep1, ep2, ep3, sigma;
	bool print_color, do_matching;
	int union_ray, thresh_ray, high_threshold, low_threshold;
	
	int *p;, *col;
	int *compM, **supressed;
	double **LX, **LY, **mag, **ang;
	std::vector<Compound>compound;
	image img,out,r,g,b;
	Detector detector;
	
	void read_params();
	void compute_gradients(); 
	void suppress();
	void union_find_join();
	void assign_colors();
	
	bool inline clos(double a, double b, double ep);
	bool inline corners_on_different_sides(int &Sx, int &Sy, double Gx, double Gy);
	double angle_from_two(double x, double y);
	
	int Find(int x);
	void Union(int x, int y);
	
	void join(int x1,int y1,int x2,int y2,image& im, int color);
	image gradient(const image& i, int high_threshold, int low_threshold, int supp_radius, int kto);
	void print_compounds(int mode, char *path);
};
//vector<Gradient> gradient(const image& i);


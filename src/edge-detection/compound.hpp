	#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include "../image/image.hpp"

class Compound{
	public:
		int const static Xbound = 1000, Ybound = 1000;
		int n;
		int cR,cB,cG;
		int ends[2];
		std::vector<int>X,Y,ind,nX,nY;
		std::vector<std::vector<int> >graf;
		std::map<int,int>mapa;
		Compound();
		image print_me();
		double dist(int i, int j);
		void deforest_me();
		void join_furthest(int mode);
		void paint_ball(image &img,int &x,int &y,int R);
};

class Detector{
	public:
		std::vector<Compound>comps;	
		std::vector<std::vector<int> >G;
};

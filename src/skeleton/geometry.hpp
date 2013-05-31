#pragma once

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

class point{
    public:
    double x,y,z;
    double dist();
    point operator+(const point P);
    point operator-(const point P);
};

class segm{
public:
    point A, B;
    segm(point A, point B);
    segm();
    double len();
}; 

class geometry{
public:
    double STR_PARAM;
    point cross_product(point P, point Q);
    double cross_val2d(point P, point Q);
    double cross_val(point P, point Q);
    double cross_val(point P, point Q, point R);
    double cross_angle(point P, point Q);
    double cross_angle(point P, point Q, point R);
    bool are_close(point P, point Q, point R);
    geometry();
};
    
    

#include "geometry.hpp"

geometry::geometry(){
	STR_PARAM = 0.1;
}

point geometry::cross_product(point P, point Q){
    point R;
    R.x = P.y*Q.z - P.z*Q.y;
    R.y = P.z*Q.x - P.x*Q.z;
    R.z = P.x*Q.y - P.y*Q.x;
    return R;
}

double geometry::cross_val2d(point P, point Q){
    return P.x*Q.y - P.y*Q.x;
}
    
double geometry::cross_val(point P, point Q){
    return P.y*Q.z - P.z*Q.y + P.z*Q.x - P.x*Q.z + P.x*Q.y - P.y*Q.x;
}
    
//punkt zaczepienia w R
double geometry::cross_val(point P, point Q, point R){
    return cross_val(P-R,Q-R);
}
    
//w zerze
double geometry::cross_angle(point P, point Q){
    //sin
    double val = cross_val(P,Q) / P.dist() / Q.dist();
    //tylko na -PI/2, PI/2 ale poki co wystarczy
    return asin(val);
}
    
double geometry::cross_angle(point P, point Q, point R){
    return cross_angle(P-R,Q-R);
}    
    
bool geometry::are_close(point P, point Q, point R){
    double v = cross_angle(P,Q,R);
    return (v < STR_PARAM && v > -STR_PARAM);
}
    
double point::dist(){
    return sqrt(x*x+y*y+z*z);
}

point point::operator+(const point P){
    point R;
    R.x = x + P.x;
    R.y = y + P.y;
    R.z = z + P.z;
    return R;
}

point point::operator-(const point P){
    point R;
    R.x = x - P.x;
    R.y = y - P.y;
    R.z = z - P.z;
    return R;
}
    
segm::segm(point A, point B){
    this->A = A;
    this->B = B;
}
segm::segm(){};

double segm::len(){
    return (A-B).dist();
}

int main(){
}


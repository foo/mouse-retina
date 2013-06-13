#pragma once

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/geometries/adapted/c_array.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
//#include <boost/geometry/geometries/adapted/std_as_linestring.hpp>
//#include <boost/geometry/multi/multi.hpp>
//using namespace boost::geometry;

#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "../dataset/dataset.hpp"
#include "../dataset/cross-section.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"
#include "../edge-detection/edge-detection.hpp"

using namespace std;

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)
typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;

void dosome();
polygon_type make_polygon(int ile, double coords[][2]);
polygon_type make_polygon_vec(int ile, std::vector<std::pair<double,double> > coords);
std::vector<polygon_type> read_polygon(std::stringstream &ss);

std::vector<polygon_type>
read_compounds_from_file(std::string slice_coords, std::string detection_params);
std::string prepare_compounds(image &slice1, std::string sc1,
							  image &slice2, std::string sc2);
void do_slice_join();

class SliceMapper{
	public:
	//given two collections of polygons (with coords from the same bounded X,Y region)
	//returns a mapping between them (not neccessarily one-to-one, e.g. some polygons
	//might divide between slices)
	
	vector<polygon_type> *poly_col[2];
	int siz[2];
	
	void initialize(vector<polygon_type> &poly_col1, 
					vector<polygon_type> &poly_col2);
	
	//first try - we join each polygon from the first collection with a polygon of highest 
	//intersection area from the second collection
	vector<int> map_collections();
		
};





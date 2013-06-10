#include "slice-joiner.hpp"

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
void dosome(){
	 	 
	

    polygon_type poly1, poly2;
    
    const double coor1[][2] = {
    		{0,0}, {0,1}, {1,1}, {1,0}, {0,0}
    };
    const double coor2[][2] = {
    		{0.5,0.5}, {0.5,1.5}, {1.5,1.5}, {1.5,0.5}, {0.5,0.5}
    };
/*
	const double coor[][2] = {
            {2.0, 1.3}, {2.4, 1.7}, {2.8, 1.8}, {3.4, 1.2}, {3.7, 1.6},
            {3.4, 2.0}, {4.1, 3.0}, {5.3, 2.6}, {5.4, 1.2}, {4.9, 0.8}, {2.9, 0.7},
            {2.0, 1.3} // closing point is opening point
    };*/
    boost::geometry::append(poly1, coor1);
    boost::geometry::append(poly2, coor2);
    
    point_type p(0.5, 0.5);
    point_type q(2, 1);

    std::cout << "within: " << (boost::geometry::within(p, poly1) ? "yes" : "no") << std::endl;
    std::cout << "within: " << (boost::geometry::within(q, poly2) ? "yes" : "no") << std::endl;
    
    std::deque<polygon_type>inters;
    boost::geometry::intersection(poly1,poly2,inters);
    
    //std::cout << boost::geometry::area(poly1);
    BOOST_FOREACH(polygon_type const& p, inters)
	    cout << boost::geometry::area(p) << endl;
    
}


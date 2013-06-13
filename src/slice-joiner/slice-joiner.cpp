#include "slice-joiner.hpp"

bool zero_area(double area){
	double eps = 0.00000001;
	return (area < eps);
}

std::vector<polygon_type> read_polygon(std::stringstream &ss){
	Compound comp;
	std::vector<std::vector<std::pair<double,double> > > c = comp.read_us(ss);
	
	std::vector<polygon_type> p;
	
	for(int i = 0; i < c.size(); i++){
		polygon_type poly = make_polygon_vec(c[i].size(), c[i]);
		if(boost::geometry::intersects(poly)){
			std::cout << "self-intersections in compound " << i << std::endl;
		}
		else p.push_back(poly);
	}
	return p;
}

polygon_type make_polygon_vec(int ile, std::vector<std::pair<double,double> > coords){
	
	polygon_type poly; 
	for(int i = 0; i < ile; i++){
	//	std::cout << coords[i][0] << " " << coords[i][1] << std::endl;
		//boost::geometry::append(poly, coords[i]);
		double c[1][2]; 
		c[0][0] = coords[i].first;
		c[0][1] = coords[i].second;
		boost::geometry::append(poly,c);
	}
	//std::cout << boost::geometry::dsv(poly) << std::endl;
	boost::geometry::correct(poly);
	//std::cout << boost::geometry::area(poly) << std::endl;
	return poly;
}

polygon_type make_polygon(int ile, double coords[][2]){
	
	polygon_type poly; 
	for(int i = 0; i < ile; i++){
	//	std::cout << coords[i][0] << " " << coords[i][1] << std::endl;
		boost::geometry::append(poly, coords[i]);
	}
	std::cout << boost::geometry::dsv(poly) << std::endl;
	boost::geometry::correct(poly);
	std::cout << boost::geometry::area(poly) << std::endl;
	return poly;
}

void SliceMapper::initialize(vector<polygon_type> &poly_col1, 
							 vector<polygon_type> &poly_col2){
					
		poly_col[0] = &poly_col1;
		poly_col[1] = &poly_col2;
		siz[0] = poly_col[0]->size();
		siz[1] = poly_col[1]->size();
		
		/*BOOST_FOREACH(polygon_type const& p, *poly_col[0]){
			std::cout << boost::geometry::area(p) << std::endl;
		}*/
}

vector<int> SliceMapper::map_collections(){
		
		double *maximal = new double[siz[0]];
		vector<int> mapping(siz[0]);
		
		std::deque<polygon_type>inters;
				
		for(int i = 0; i < siz[0]; i++){
			maximal[i] = 0;
			mapping[i] = i;
			
			for(int j = 0; j < siz[1]; j++){
				inters.clear();
    			boost::geometry::intersection((*poly_col[0])[i],
    										  (*poly_col[1])[j],inters);
    			
				double inter_area = 0;
				BOOST_FOREACH(polygon_type const& p, inters){
					//we assume no holes are present in polygons
					inter_area += boost::geometry::area(p);
				}
				if(!zero_area(inter_area)) 
					std::cout << "area " << i << " " << j << " = " << inter_area << endl;
					
				if(!zero_area(inter_area) && inter_area > maximal[i]){
					maximal[i] = inter_area;
					mapping[i] = j;
				}
			}
		}
		
		return mapping;
	}
	
//For now we will use a very inefficient way, by just invoking edge-detectors image generating
//function for the purpose of generating compound-description files

std::vector<polygon_type>
read_compounds_from_file(std::string slice_coords, std::string detection_params)
{			
	std::stringstream pp;		
	pp <<"../output/edge-detection/compounds"+slice_coords+detection_params+".out";
						
	boost::filesystem::ifstream compound_reader(boost::filesystem::path(pp.str()));
  	int num;
	std::stringstream ss;
  	while(compound_reader>>num){
  		//std::cout << num << endl;
  		ss<<num<<" ";
  	}
	
	return read_polygon(ss);
}

std::string prepare_compounds(image &slice1, std::string sc1,
							  image &slice2, std::string sc2){
	//dataset-path = ../images/e1088_mag1_small
	
	int th = 60;
	int tl = 10;
	int sr = 1;
	double ep1 = 0.3;
	double ep2 = 0.3;
	double ep3 = 0.3;
	int ur = 3;
	int tr = 2;
	
	std::stringstream ss1;
	ss1 << "_" << th << "_" << tl << "_" << sr;
	
	image i1;
	rgb_image i2,i3;
	
	//TODO: add reading from a cfg file, moron
	std::tie(i1, i2, i3) = 
	detect_edges(slice1, th, tl, sr, 0, ep1, ep2, ep3, 0, 0, ur, tr, sc1);
	
	{
		std::stringstream ss;
		ss << "../output/edge-detection/edge_detection" << th << "_"<< tl << "_" << sr<< ".ppm";

		std::cerr << "Exporting image to " << ss.str() << std::endl;
		ppm_export(i2, boost::filesystem::path(ss.str()));
    }
            
	detect_edges(slice2, th, tl, sr, 0, ep1, ep2, ep3, 0, 0, ur, tr, sc2);
	
	return ss1.str();
}

//add parameters for slices coordinates
void do_slice_join(){
	int x1[2] = {50,50};
	int y1[2] = {50,50};
	int x2[2] = {320,320};
	int y2[2] = {320,320};
	int z[2] = {120,130};
	
	//get slices
	dataset d("../images/e1088_mag1_small");
	
	image slice1 = gaussian(cross_section_z(d,x1[0],x2[0],y1[0],y2[0],z[0]), 1.1);
	image slice2 = gaussian(cross_section_z(d,x1[1],x2[1],y1[1],y2[1],z[1]), 1.1);
	std::stringstream slice_coords[2]; 
	for(int i = 0; i < 2; i++){
		slice_coords[i] << x1[i] << "#";
		slice_coords[i] << x2[i] << "#";
		slice_coords[i] << y1[i] << "#";
		slice_coords[i] << y2[i] << "#";
		slice_coords[i] << z[i] << "#";
	}
	
	//make edge-detector generate compounds
	std::string detection_params = prepare_compounds(slice1, slice_coords[0].str(),
													 slice2, slice_coords[1].str());
	
	//read generated compounds
	std::vector<polygon_type> poly[2];
	
	for(int i = 0; i < 2; i++)
		poly[i] = read_compounds_from_file(slice_coords[i].str(), detection_params);
	
	//join compounds
	SliceMapper mapper;
	mapper.initialize(poly[0], poly[1]);
	
	//two way mapping = thing about it!
	std::vector<int>mapping = mapper.map_collections();
}

void dosome(){
	 	 
    polygon_type poly1, poly2;
    
    const double coor1[][2] = {
    		{0,0}, {0,1}, {1,1}, {1,0}, {0,0}
    };
    boost::geometry::append(poly1, coor1);
    std::cout << boost::geometry::area(poly1) << " & " << endl;
    const double coor2[][2] = {
    		{0.5,0.5}, {0.5,1.5}, {1.5,1.5}, {1.5,0.5}, {0.5,0.5}
    };
    
}

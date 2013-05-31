#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "../dataset/dataset.hpp"
#include "../dataset/cross-section.hpp"
#include "../image/image.hpp"
#include "../image/pgm-export.hpp"

#include "../filters/sobel.hpp"
#include "../filters/gaussian.hpp"
#include "../filters/sharpen.hpp"
#include "../filters/threshold.hpp"
#include "../filters/dilation.hpp"
#include "../edge-detection/gradient.hpp"

int main(int argc, char* argv[])
{
  const char* const dataset_dir = "../images/e1088_mag1_small";
  dataset d(dataset_dir);

  std::cerr << "Obtaining image from grid." << std::endl;
  
  //image i = cross_section(d, 10, 300, 10, 300, 100);
  image i = cross_section_z(d, 50, 320, 50, 320, 120);
  gaussian(i,0.8408964);
  
  {
    std::cerr
      << "Exporting original image to output/edge-detection/original.pgm."
      << std::endl;
  
    pgm_export(i, boost::filesystem::path(
	"../output/edge-detection/original.pgm"));
	
    pgm_export(sharpen(i), boost::filesystem::path(
	"../output/edge-detection/original_gauss.pgm"));
  }

  {
    std::cerr
      << "Edge detection."
      << std::endl;
      
    FILE * params = fopen("../src/edge-detection/params.conf", "r");  
    char name[20]={0}; 
	int sup_rad1, sup_rad2;
	int thresh_high1, thresh_high2;
	int thresh_diff1, thresh_diff2;
	
	while(fscanf(params, "%s", name)!=EOF){
		if(strcmp(name,"sup_rad1")==0) fscanf(params,"%d", &sup_rad1);
		if(strcmp(name,"sup_rad2")==0) fscanf(params,"%d", &sup_rad2);
		if(strcmp(name,"thresh_high1")==0) fscanf(params,"%d", &thresh_high1);
		if(strcmp(name,"thresh_high2")==0) fscanf(params,"%d", &thresh_high2);
		if(strcmp(name,"thresh_diff1")==0) fscanf(params,"%d", &thresh_diff1);
		if(strcmp(name,"thresh_diff2")==0) fscanf(params,"%d", &thresh_diff2);
	}
	fclose(params);
	
	for(int supp_radius = sup_rad1; supp_radius <= sup_rad2; supp_radius++)
    for(int thigh = thresh_high1; thigh <= thresh_high2; thigh += 10)
    //for(int which = 0; which < 20; which+=100)
    for(int tlow = thigh-thresh_diff1; tlow <= thigh-thresh_diff2; tlow += 10)
    {
      image i_edge_detection =
      gradient(i,thigh,tlow,supp_radius,0);
      /*gradient(
			//sobel(
			  sharpen(
			gaussian5x5(i)),
		 thigh, tlow, supp_radius, which);*/
  		/*
      image i_edge_detection_with_dilation =
      gradient(
		  erosion(
			dilation(
			sobel(
			  sharpen(
				gaussian5x5(i))))), threshold_value);
		*/
		
      {
	std::stringstream ss;
	ss << "../output/edge-detection/edge_detection" << thigh << "_"<< tlow << "_" << supp_radius<<"_" << 0 <<".pgm";
      
	std::cerr	<< "Exporting image to " << ss.str() << std::endl;
	pgm_export(i_edge_detection, boost::filesystem::path(ss.str()));
      }/*
      {
	std::stringstream ss;
	ss << "../output/edge-detection/edge_detection_minkowski" << threshold_value << ".pgm";
      
	std::cerr	<< "Exporting image to " << ss.str() << std::endl;
	pgm_export(i_edge_detection_with_dilation, boost::filesystem::path(ss.str()));
      }*/
    }
  }

  std::cerr << "Program finished successfully." << std::endl;

  return 0;
}

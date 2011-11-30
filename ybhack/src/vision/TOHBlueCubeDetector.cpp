/**
 * @file TestFilter.h
 * @author Shaikh Sonny Aman
 */
#include "vision/TOHBlueCubeDetector.h"

using namespace cvb;

namespace aanpr{
	unsigned char TOHBlueCubeDetector::updatePixel( double r, double g, double b){
		return 255*((b>0.2+r)&&(b>0.2+g));
	}
	TOHBlueCubeDetector::~TOHBlueCubeDetector(){
		std::cout << "BlueObjectFilter destructed \n";
	}
}

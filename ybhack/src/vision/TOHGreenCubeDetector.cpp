/**
 * @file TestFilter.h
 * @author Shaikh Sonny Aman
 */

#include "vision/TOHGreenCubeDetector.h"

using namespace cvb;

namespace aanpr{
	unsigned char TOHGreenCubeDetector::updatePixel( double r, double g, double b){
			return 255*((g>r)&&(g>b));
	}
	TOHGreenCubeDetector::~TOHGreenCubeDetector(){
		std::cout << "TOHGreenCubeDetector destructed \n";
	}

}

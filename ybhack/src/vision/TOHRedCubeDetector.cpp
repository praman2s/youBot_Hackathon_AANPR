/**
 * @file TestFilter.h
 * @author Shaikh Sonny Aman
 */
#include "vision/TOHRedCubeDetector.h"
namespace aanpr{
	unsigned char TOHRedCubeDetector::updatePixel( double r, double g, double b){
			return 255*((r>0.2+g)&&(r>0.2+b));
	}

	TOHRedCubeDetector::~TOHRedCubeDetector(){
		std::cout << "RedObjectFilter destructed \n";
	}
}

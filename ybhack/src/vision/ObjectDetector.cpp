/*
 * Object2DDetector.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: aman
 */

#include "vision/ObjectDetector.h"

namespace aanpr {

ObjectDetector::ObjectDetector() {
}

ObjectDetector::~ObjectDetector() {
	clearObjectList();
}
void ObjectDetector::clearObjectList(){
	for( size_t i=0; i < objectList.size(); i++ ){
		delete objectList[ i ];
	}
	objectList.clear();
}
} /* namespace aanpr */

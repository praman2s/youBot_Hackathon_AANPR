/*
 * Object2DDetector.h
 *
 *  Created on: Nov 30, 2011
 *      Author: aman
 */

#ifndef OBJECT2DDETECTOR_H_
#define OBJECT2DDETECTOR_H_

#include <vector>
#include "vision/Object2D.h"

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace aanpr {

class ObjectDetector {
public:
	ObjectDetector();
	virtual ~ObjectDetector();
	virtual void detectObject( cv::Mat &image ) = 0;
	std::vector< vision::Object2D* > objectList;
	void clearObjectList();
};

} /* namespace aanpr */
#endif /* OBJECT2DDETECTOR_H_ */

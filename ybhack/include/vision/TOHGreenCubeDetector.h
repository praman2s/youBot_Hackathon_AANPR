/**
 * @file TestFilter.h
 * @author Shaikh Sonny Aman
 */
#ifndef ___GREEN_OBJECT_FILTER_H_
#define ___GREEN_OBJECT_FILTER_H_

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <cvblob.h>
#include "vision/TOHObjectDetector.h"

namespace aanpr{
using namespace cvb;

/**
 * @class TestFilter A test filter to play with opencv
 */
class TOHGreenCubeDetector : public TOHObjectDetector{
public:
	virtual unsigned char updatePixel( double r, double g, double b);
	virtual  ~TOHGreenCubeDetector();
	virtual string getColor(){
			return "green";
	}
};
}

#endif

/**
 * @file TestFilter.h
 * @author Shaikh Sonny Aman
 */
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ybhack/ImageGrabber.h"

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <cvblob.h>

#ifndef ___GREEN_OBJECT_FILTER_H_
#define ___GREEN_OBJECT_FILTER_H_
/**
 * @class TestFilter A test filter to play with opencv
 */

using namespace cvb;

namespace aanpr{
class GreenObjectFilter : public ImageFilter{
public:
	virtual unsigned char updatePixel( double r, double g, double b){
			return 255*((g>r)&&(g>b));
	}
	virtual  ~GreenObjectFilter(){
		std::cout << "Test filter destructed \n";
	}
};
}

#endif

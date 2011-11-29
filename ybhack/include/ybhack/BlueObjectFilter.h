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

#ifndef ___BLUE_OBJECT_FILTER_H_
#define ___BLUE_OBJECT_FILTER_H_
/**
 * @class TestFilter A test filter to play with opencv
 */

using namespace cvb;

namespace aanpr{
class BlueObjectFilter : public ImageFilter{
public:
	virtual unsigned char updatePixel( double r, double g, double b){
		return 255*((b>0.2+r)&&(b>0.2+g));
	}
	virtual  ~BlueObjectFilter(){
		std::cout << "Test filter destructed \n";
	}
};
}

#endif

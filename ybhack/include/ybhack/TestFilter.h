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


#ifndef __TEST_FILTER_H__
#define __TEST_FILTER_H__
/**
 * @class TestFilter A test filter to play with opencv
 */

namespace aanpr{
class TestFilter : public ImageFilter{
public:
	virtual void filter( cv::Mat& image ){
		std::cout << "in test filter \n";
		cv::circle(image, cv::Point(300, 50), 10, CV_RGB(255,0,0));
	}
	virtual  ~TestFilter(){
		std::cout << "Test filter destructed \n";
	}
};
}

#endif

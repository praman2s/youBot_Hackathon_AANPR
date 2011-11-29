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

#ifndef __TEST_FILTER_H__
#define __TEST_FILTER_H__
/**
 * @class TestFilter A test filter to play with opencv
 */

using namespace cvb;

namespace aanpr{
class TestFilter : public ImageFilter{
public:
	virtual void filter( cv::Mat& image ){
		///*
		IplImage *img= new IplImage(image);

		//plImage* img = image.IplImage;
		IplImage *gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
		cvCvtColor(img, gray, CV_BGR2GRAY);
		cvThreshold(gray, gray, 150, 255, CV_THRESH_BINARY);

		IplImage *labelImg=cvCreateImage(cvGetSize(gray), IPL_DEPTH_LABEL, 1);
		CvBlobs blobs;
		unsigned int result=cvLabel(gray, labelImg, blobs);

		cvRenderBlobs(labelImg, blobs, img, img);
//*/
		cv::circle(image, cv::Point(300, 50), 10, CV_RGB(255,0,0));

	}
	virtual  ~TestFilter(){
		std::cout << "Test filter destructed \n";
	}
};
}

#endif

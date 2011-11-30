/**
 * Originally taken from
 * http://www.ros.org/wiki/cv_bridge/Tutorials/UsingCvBridgeToConvertBetweenROSImagesAndOpenCVImages
 */
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/ptr_container/ptr_list.hpp>


#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <cvblob.h>
#include <vector>
#include <iostream>
#include "vision/ObjectDetector.h"
#include "vision/TOHCube.h";

#ifndef __IMAGE_FILTER_H__
#define __IMAGE_FILTER_H__

/**
 * This interface works as delegate to ImageGrabber.
 *
 * Just before showing the image on the cv window, the image is passed to the delegate
 * to work on it.
 */

namespace aanpr{

class TOHObjectDetector : public ObjectDetector{
public:
	TOHObjectDetector();
	virtual unsigned char updatePixel( double r, double g, double b) = 0;
	void detectObject( cv::Mat &image );
	virtual string getColor() =0;
	virtual ~TOHObjectDetector(){}

	unsigned int numberOfObjects;

	double minCenterX;
	double minCenterY;
	double maxCenterX;
	double maxCenterY;
	double minArea;
	double maxArea;

	double avgCenterY;

	void lookFar();
	void lookNear();
	void justLook();

	double getXOffset();

	double getRotation();

private:
	const int MIN_AREA_FILTER;
	const int MAX_AREA_FILTER;
	const int DEFAUL_AREA_FILTER;
	const int ZOOM_STEP;

	int minAreaFilter;
	int maxAreaFilter;

	int imageCols;
	int imageRows;

	cv::Mat* lastImage;
};
}

#endif

/**
 * @file TestFilter.h
 * @author Shaikh Sonny Aman
 */

#ifndef __IMAGE_GRABBER_H__
#define __IMAGE_GRABBER_H__

#include <ros/ros.h>

#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/ptr_container/ptr_list.hpp>

#include "vision/CVWindow.h"

namespace aanpr{

class ImageGrabber;

/**
 * @class ImageGrabberDelegate
 * @brief Delegate to the ImageGrabber must inherit this class.
 * When ImageGrabber grabs an image, delegates OnIMageGrabbed method is called
 * with the image grabbed.
 */
class ImageGrabberDelegate{
public:
	/**
	 * This is the delegate method is called when the ImageGrabber grabs an image
	 * @param grabber Reference to the grabber which grabbed the image
	 * @param image The grabbed image
	 */
	virtual void OnImageGrabbed( ImageGrabber* grabber, cv::Mat& image )=0;

	virtual ~ImageGrabberDelegate(){}
};


/**
 * @class ImageGrabber
 * @brief This class grabs image from a topic
 */
class ImageGrabber{
public:
	ImageGrabber();
	~ImageGrabber();

	/**
	 * This method starts subscribing to a topic
	 */
	void grabImageFromTopic( const std::string topicName );

	/**
	 * Callback method for topic subscriber. Image data extracted here
	 * and converted to cv::Mat.
	 *
	 * @param msg Message received from the topic
	 */
	void topicCallback( const sensor_msgs::ImageConstPtr& msg );

	/**
	 * Delegate to the grabber
	 */
	ImageGrabberDelegate* delegate;
private:
	ros::NodeHandle hNode;
	image_transport::ImageTransport imageTransport;
	image_transport::Subscriber imageSubscriber;

	std::string topicName;
	vision::CVWindow* cvWin;
};

}

#endif

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

#ifndef __IMAGE_GRABBER_H__
#define __IMAGE_GRABBER_H__

/**
 * This interface works as delegate to ImageGrabber.
 *
 * Just before showing the image on the cv window, the image is passed to the delegate
 * to work on it.
 */

namespace aanpr{

class ImageFilter{
public:
	virtual void filter( cv::Mat& image )=0;
};

namespace enc = sensor_msgs::image_encodings;

static const char WINDOW[] = "Image window";

class ImageGrabber
{

  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

  boost::ptr_list<ImageFilter> filterList;
  boost::ptr_list<ImageFilter>::iterator iterFilterList;


public:
  ImageGrabber()
    : it_(nh_)
  {
    image_pub_ = it_.advertise("image_out", 1);
    image_sub_ = it_.subscribe("image_raw", 1, &ImageGrabber::imageCb, this);

    cv::namedWindow(WINDOW);
  }

  ~ImageGrabber()
  {
	  filterList.clear();
    cv::destroyWindow(WINDOW);
  }

  void addFilter( ImageFilter* filter ){
	  filterList.push_back( filter );
  }
  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, enc::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    //if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
      //cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

    cv::Mat img = cv_ptr->image;

    for (iterFilterList = filterList.begin();
    		iterFilterList != filterList.end();
    		iterFilterList++)
       {
          iterFilterList->filter( img );
       }

    cv::imshow(WINDOW, img);
    cv::waitKey(3);

    image_pub_.publish(cv_ptr->toImageMsg());
  }
};

}

#endif

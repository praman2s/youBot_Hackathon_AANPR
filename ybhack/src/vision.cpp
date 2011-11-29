#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ybhack/ImageGrabber.h"
#include "ybhack/TestFilter.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  aanpr::TestFilter tf;
  aanpr::ImageGrabber ic;
  ic.addFilter( &tf );
  ros::spin();
  return 0;
}

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "vision/ImageGrabber.h"
#include "vision/VisionController.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");

  aanpr::VisionController vc;
  aanpr::ImageGrabber ic;
  ic.delegate = &vc;
  ic.grabImageFromTopic( "image_raw" );
  ros::spin();
  return 0;
}

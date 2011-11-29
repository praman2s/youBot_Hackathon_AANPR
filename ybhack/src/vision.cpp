#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ybhack/ImageGrabber.h"
#include "ybhack/TestFilter.h"
#include "ybhack/RedObjectFilter.h"
#include "ybhack/GreenObjectFilter.h"
#include "ybhack/BlueObjectFilter.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  aanpr::RedObjectFilter rf;
  aanpr::GreenObjectFilter gf;
  aanpr::BlueObjectFilter bf;
  aanpr::ImageGrabber ic;
  ic.addFilter( &rf );
  ic.addFilter( &gf );
  ic.addFilter( &bf );
  ros::spin();
  return 0;
}

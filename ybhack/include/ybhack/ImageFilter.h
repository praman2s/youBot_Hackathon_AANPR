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
#ifndef __IMAGE_FILTER_H__
#define __IMAGE_FILTER_H__

/**
 * This interface works as delegate to ImageGrabber.
 *
 * Just before showing the image on the cv window, the image is passed to the delegate
 * to work on it.
 */
using namespace cvb;
namespace aanpr{

class ImageFilter{
public:
	void filter( cv::Mat& image ){
			///*
			 CvTracks tracks;
			IplImage *img= new IplImage(image);

			CvSize imgSize = cvGetSize(img);

			  IplImage *frame = cvCreateImage(imgSize, img->depth, img->nChannels);

			  IplConvKernel* morphKernel = cvCreateStructuringElementEx(5, 5, 1, 1, CV_SHAPE_RECT, NULL);

			  //unsigned int frameNumber = 0;
			  unsigned int blobNumber = 0;

			  bool quit = false;
			 // while (!quit)
			  {
			    //IplImage *img = cvRetrieveFrame(capture);

			    cvConvertScale(img, frame, 1, 0);

			    IplImage *segmentated = cvCreateImage(imgSize, 8, 1);

			    // Detecting red pixels:
			    // (This is very slow, use direct access better...)
			    for (unsigned int j=0; j<imgSize.height; j++)
			      for (unsigned int i=0; i<imgSize.width; i++)
			      {
			        CvScalar c = cvGet2D(frame, j, i);

			        double b = ((double)c.val[0])/255.;
			        double g = ((double)c.val[1])/255.;
			        double r = ((double)c.val[2])/255.;
			        unsigned char f = updatePixel( r, g, b);

			        cvSet2D(segmentated, j, i, CV_RGB(f, f, f));
			      }

			    cvMorphologyEx(segmentated, segmentated, NULL, morphKernel, CV_MOP_OPEN, 1);

			    //cvShowImage("segmentated", segmentated);

			    IplImage *labelImg = cvCreateImage(cvGetSize(frame), IPL_DEPTH_LABEL, 1);

			    CvBlobs blobs;
			    unsigned int result = cvLabel(segmentated, labelImg, blobs);
			    std::cout<< blobs.size() << "\n";
			    for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
			    {
			      cout << "Blob #" << it->second->label << ": Area=" << it->second->area << ", Centroid=(" << it->second->centroid.x << ", " << it->second->centroid.y << ")" << endl;
			    }

			    cvFilterByArea(blobs, 500, 1000000);
			    cvRenderBlobs(labelImg, blobs, frame, frame, CV_BLOB_RENDER_BOUNDING_BOX);
			    cvUpdateTracks(blobs, tracks, 200., 5);
			    cvRenderTracks(tracks, frame, frame, CV_TRACK_RENDER_ID|CV_TRACK_RENDER_BOUNDING_BOX);

			    image= cv::Mat(frame, 1);
			   // cvShowImage("red_object_tracking", frame);

			    /*std::stringstream filename;
			    filename << "redobject_" << std::setw(5) << std::setfill('0') << frameNumber << ".png";
			    cvSaveImage(filename.str().c_str(), frame);*/

			    cvReleaseImage(&labelImg);
			    cvReleaseImage(&segmentated);

			    cvReleaseBlobs(blobs);

			    //frameNumber++;
			  }

			  cvReleaseStructuringElement(&morphKernel);
			  cvReleaseImage(&frame);

			  cvDestroyWindow("red_object_tracking");

		}
	virtual unsigned char updatePixel( double r, double g, double b) = 0;
};
}

#endif

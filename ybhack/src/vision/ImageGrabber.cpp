#include "vision/ImageGrabber.h"

namespace enc = sensor_msgs::image_encodings;

namespace aanpr{

ImageGrabber::ImageGrabber(): imageTransport(hNode),delegate(0), cvWin(0) {
}

ImageGrabber::~ImageGrabber(){
	 //filterList.clear();
	if( cvWin ){
		delete cvWin;
	}
 }

void ImageGrabber::grabImageFromTopic( const std::string topic ){
	topicName = topic;

	if( cvWin ){
		delete cvWin;
	}

	cvWin = new vision::CVWindow("ImageGrabber :: " + topic );
	cvWin->show();
	imageSubscriber.shutdown();
	imageSubscriber = imageTransport.subscribe( topicName, 1, &ImageGrabber::topicCallback, this);
}
//void ImageGrabber::addFilter( TOHObjectDetector* filter ){
	//filterList.push_back( filter );
//}
void ImageGrabber::topicCallback( const sensor_msgs::ImageConstPtr& msg ){
	cv_bridge::CvImagePtr cv_ptr;

	try{
		cv_ptr = cv_bridge::toCvCopy(msg, enc::BGR8);
	}
	catch (cv_bridge::Exception& e){
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	cvWin->update( cv_ptr->image );

	if( delegate ){
		delegate->OnImageGrabbed( this, cv_ptr->image );
	}
//	for (iterFilterList = filterList.begin();
//	iterFilterList != filterList.end();
//	iterFilterList++)
//	{
//	((TOHObjectDetector*)iterFilterList)->filter( img );
//	}
//
}

}


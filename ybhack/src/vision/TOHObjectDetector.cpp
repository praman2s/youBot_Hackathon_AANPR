/**
 * Originally taken from
 * http://www.ros.org/wiki/cv_bridge/Tutorials/UsingCvBridgeToConvertBetweenROSImagesAndOpenCVImages
 */
#include "vision/TOHObjectDetector.h"
using namespace cvb;

namespace aanpr{
TOHObjectDetector::TOHObjectDetector(): minAreaFilter( 1000 )
										, MIN_AREA_FILTER( 100 )
										, MAX_AREA_FILTER( 30000 )
										, DEFAUL_AREA_FILTER( 1000 )
										, ZOOM_STEP( 100 )
										, maxAreaFilter( 18000 ){

}
void TOHObjectDetector::lookFar(){
	minAreaFilter = minAreaFilter - ZOOM_STEP;
	if( minAreaFilter > MAX_AREA_FILTER ){
		minAreaFilter = MAX_AREA_FILTER; // max area
	}
}
void TOHObjectDetector::lookNear(){
	minAreaFilter = minAreaFilter - ZOOM_STEP;
	if( minAreaFilter < MIN_AREA_FILTER ){
		minAreaFilter = MIN_AREA_FILTER; // min area
	}
}
void TOHObjectDetector::justLook(){
	minAreaFilter = DEFAUL_AREA_FILTER;
}

void TOHObjectDetector::detectObject( cv::Mat &image ){
	lastImage = &image;

	CvTracks tracks;
	IplImage *img= new IplImage(image);

	CvSize imgSize = cvGetSize(img);

	IplImage *frame = cvCreateImage(imgSize, img->depth, img->nChannels);

	IplConvKernel* morphKernel = cvCreateStructuringElementEx(5, 5, 1, 1, CV_SHAPE_RECT, NULL);

	unsigned int blobNumber = 0;

	cvConvertScale(img, frame, 1, 0);

	IplImage *segmentated = cvCreateImage(imgSize, 8, 1);

	// Detecting red pixels:
	// (This is very slow, use direct access better...)
	for (unsigned int j=0; j<imgSize.height; j++)
	for (unsigned int i=0; i<imgSize.width; i++){
		CvScalar c = cvGet2D(frame, j, i);

		double b = ((double)c.val[0])/255.;
		double g = ((double)c.val[1])/255.;
		double r = ((double)c.val[2])/255.;
		unsigned char f = updatePixel( r, g, b);

		cvSet2D(segmentated, j, i, CV_RGB(f, f, f));
	}

	cvMorphologyEx(segmentated, segmentated, NULL, morphKernel, CV_MOP_OPEN, 1);
	IplImage *labelImg = cvCreateImage(cvGetSize(frame), IPL_DEPTH_LABEL, 1);

	CvBlobs blobs;
	unsigned int result = cvLabel(segmentated, labelImg, blobs);
	//std::cout<< blobs.size() << "\n";

	clearObjectList();
	numberOfObjects = 0;


	minCenterX = minCenterY = minArea = INT_MAX;
	maxCenterX = maxCenterY = maxArea =  0;

	imageCols = imageRows = 0;

	avgCenterY = -1;
	double totalCenterY = 0;

	for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it){
		if( it->second->area < minAreaFilter || it->second->area > maxAreaFilter )continue;
		vision::TOHCube* cube = new vision::TOHCube();
		cube->color = getColor();

		cube->centerX = it->second->centroid.x;
		cube->centerY = it->second->centroid.y;
		totalCenterY += cube->centerY;

		cube->maxX = it->second->maxx;
		cube->maxY = it->second->maxy;

		cube->minX = it->second->minx;
		cube->minY = it->second->miny;

		cube->area = it->second->area;

		objectList.push_back( cube );

		numberOfObjects++;

		if( minCenterX > cube->centerX ) minCenterX = cube->centerX;
		if( minCenterY > cube->centerY ) minCenterY = cube->centerY;
		if( maxCenterX < cube->centerX ) maxCenterX = cube->centerX;
		if( maxCenterY < cube->centerY ) maxCenterY = cube->centerY;

		if( minArea > cube->area ) minArea = cube->area;
		if( maxArea < cube->area ) maxArea = cube->area;

		imageCols = image.cols;
		imageRows = image.rows;

	}

	avgCenterY = totalCenterY/numberOfObjects;

	cvFilterByArea(blobs, minAreaFilter, maxAreaFilter );
	cvRenderBlobs(labelImg, blobs, frame, frame, CV_BLOB_RENDER_BOUNDING_BOX|CV_BLOB_RENDER_CENTROID);
	//cvUpdateTracks(blobs, tracks, 200., 5);
	//cvRenderTracks(tracks, frame, frame, CV_TRACK_RENDER_ID|CV_TRACK_RENDER_BOUNDING_BOX);

	image= cv::Mat(frame, 1);


	cvReleaseImage(&labelImg);
	cvReleaseImage(&segmentated);

	cvReleaseBlobs(blobs);

	cvReleaseStructuringElement(&morphKernel);
	cvReleaseImage(&frame);

	//cvDestroyWindow("red_object_tracking");

}

double TOHObjectDetector::getXOffset(){
	if( numberOfObjects < 1) return 0;

	double total = 0;
	for( int i=0; i < numberOfObjects; i++ ){
		total += objectList[ i ]->centerX;
	}
	//cout << "\n Cols = " << imageCols << endl;
	return imageCols/2 - total/numberOfObjects;
}

double TOHObjectDetector::getRotation(){
	if( numberOfObjects < 2) return 0;

	vector< vision::Object2D* > tmp;
	for( int i = 0; i< numberOfObjects; i++ ){
		tmp.push_back( objectList[i] );
	}


	// sort by x
	for( int i = 0; i< numberOfObjects - 1; i++ ){
		for( int j = i; j< numberOfObjects; j++ ){
			if( tmp[ i ]->centerX > tmp[ j ]->centerX ){
				cout << i << "," << j << endl;
				vision::Object2D* c = tmp[ i ];
				tmp[ i ] = tmp[ j ];
				tmp[ j ] = c;
			}
		}
	}
	cv::line( *lastImage
				, cv::Point( tmp.front()->centerX, tmp.front()->centerY)
				, cv::Point( tmp.back()->centerX, tmp.back()->centerY)
				, cv::Scalar(0,255,0,0)
				, 2, 8, 0
				);
	double rot = tmp.front()->centerY - tmp.back()->centerY;
	tmp.clear();
	return rot;
}

}// end namespace

/*
 * VisionController.cpp
 *
 *  Created on: Nov 29, 2011
 *      Author: aman
 */

#include "vision/VisionController.h"
#include <stdio.h>

namespace aanpr {

VisionController::VisionController() {
	winCV = new vision::CVWindow("Vision Controller");
	winCV->show();
}

VisionController::~VisionController() {
	if( winCV ){
		delete winCV;
	}
}

void VisionController::OnImageGrabbed( ImageGrabber* grabber, cv::Mat& image ){

	cdBlue.detectObject( image );
	cdGreen.detectObject( image );
	cdRed.detectObject( image );
	image.cols;
	int numBlue = cdBlue.numberOfObjects;
	int numRed = cdRed.numberOfObjects;
	int numGreen = cdGreen.numberOfObjects;

	cout << " R:G:B = " << numRed << ":" << numGreen << ":" << numBlue << std::endl;

	//cout << " Red:: min -> max =  " << cdRed.minArea << "->" << cdRed.maxArea << std::endl;
	//cout << " Green:: min -> max =  " << cdGreen.minArea << "->" << cdGreen.maxArea << std::endl;
	//cout << " Blue:: min -> max =  " << cdBlue.minArea << "->" << cdBlue.maxArea << std::endl;

	cout << "\nBlue offset: " << cdBlue.getXOffset() << ", posx:" << cdBlue.minCenterX << std::endl;
	cout << "\n Rotation R:G:B = " << cdRed.getRotation() << ":" << cdGreen.getRotation() << ":" << cdBlue.getRotation() << std::endl;

	vector<string> layerColors(3);
	vector<double> layerPosition(3);

	layerColors[0] = "red";
	layerColors[1] = "green";
	layerColors[2] = "blue";

	layerPosition[0] = cdRed.avgCenterY;
	layerPosition[1] = cdGreen.avgCenterY;
	layerPosition[2] = cdBlue.avgCenterY;

	printf("\n Layers = %s(%f) -> %s(%f)->%s(%f) \n"
				,layerColors[0].c_str(),layerPosition[0]
			  ,layerColors[1].c_str(),layerPosition[1]
			,layerColors[2].c_str(),layerPosition[2]
		);

	for( int i = 0; i< 2; i++ ){
		for( int j = i; j< 3; j++ ){
			if( layerPosition[i] > layerPosition[j] ){
				double tmp = layerPosition[i];
				layerPosition[i] = layerPosition[j];
				layerPosition[j] = tmp;

				string tmps = layerColors[i];
				layerColors[i] = layerColors[j];
				layerColors[j] = tmps;
			}
		}
	}
	printf("\n Layers = %s(%f) -> %s(%f)->%s(%f) \n"
			,layerColors[0].c_str(),layerPosition[0]
		  ,layerColors[1].c_str(),layerPosition[1]
		,layerColors[2].c_str(),layerPosition[2]
	);

	winCV->update( image );
}

} /* namespace aanpr */

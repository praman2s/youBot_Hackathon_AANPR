/*
 * CVWindow.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: aman
 */

#include "vision/CVWindow.h"

namespace aanpr {
namespace vision {

CVWindow::CVWindow( string name ):windowName(name), isVisible(0) {
}

CVWindow::~CVWindow() {
	hide();
}

void CVWindow::show(){
	if( !isVisible ){
		cv::namedWindow( windowName );
	}
	isVisible = 1;
}
void CVWindow::hide(){
	if( isVisible ){
		cout << "\nHiding Window: " << windowName << "\n";
		cv::destroyWindow( windowName );
	}
	isVisible = 0;
}
void CVWindow::update( cv::Mat &image ){
	if( isVisible ){
		cv::imshow( windowName, image );
		cv::waitKey(3);
	}
}

} /* namespace vision */
} /* namespace aanpr */

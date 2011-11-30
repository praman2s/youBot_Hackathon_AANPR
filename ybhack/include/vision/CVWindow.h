/*
 * CVWindow.h
 *
 *  Created on: Nov 30, 2011
 *      Author: aman
 */

#ifndef CVWINDOW_H_
#define CVWINDOW_H_

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace std;

namespace aanpr {
namespace vision {

class CVWindow {
public:
	CVWindow( string name );
	virtual ~CVWindow();
	void show();
	void hide();
	void update( cv::Mat &image );
private:
	int isVisible;
	string windowName;
};

} /* namespace vision */
} /* namespace aanpr */
#endif /* CVWINDOW_H_ */

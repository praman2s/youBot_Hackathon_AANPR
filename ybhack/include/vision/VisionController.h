/*
 * VisionController.h
 *
 *  Created on: Nov 29, 2011
 *      Author: aman
 */

#ifndef VISIONCONTROLLER_H_
#define VISIONCONTROLLER_H_

#include "vision/ImageGrabber.h"
#include "vision/TOHGreenCubeDetector.h"
#include "vision/TOHRedCubeDetector.h"
#include "vision/TOHBlueCubeDetector.h"

#include <map>

namespace aanpr {

/**
 * @class VisionController
 * @brief This class encapsulates all vision processing
 * and develops some assumption about the environment.
 */
class VisionController : public ImageGrabberDelegate{
public:
	VisionController();
	virtual ~VisionController();
	virtual void OnImageGrabbed( ImageGrabber* grabber, cv::Mat& image );

	TOHGreenCubeDetector cdGreen;
	TOHBlueCubeDetector cdBlue;
	TOHRedCubeDetector cdRed;

	vision::CVWindow* winCV;

};

} /* namespace aanpr */


#endif /* VISIONCONTROLLER_H_ */

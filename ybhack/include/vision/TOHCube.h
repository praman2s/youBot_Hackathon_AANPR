/*
 * TOHCube.h
 *
 *  Created on: Nov 30, 2011
 *      Author: aman
 */

#ifndef TOHCUBE_H_
#define TOHCUBE_H_

#include "Object2D.h"
#include <iostream>
#include <string>

using namespace std;
namespace aanpr {
namespace vision {

class TOHCube: public aanpr::vision::Object2D {
public:
	TOHCube();
	virtual ~TOHCube();
	string color; // string comparison is really expensive!
};

} /* namespace vision */
} /* namespace aanpr */
#endif /* TOHCUBE_H_ */

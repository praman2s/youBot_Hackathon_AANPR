/*
 * Object2D.h
 *
 *  Created on: Nov 30, 2011
 *      Author: aman
 */

#ifndef OBJECT2D_H_
#define OBJECT2D_H_

namespace aanpr {
namespace vision {

class Object2D {
public:
	Object2D();
	virtual ~Object2D();

	double centerX;
	double centerY;
	double maxX;
	double maxY;
	double minX;
	double minY;
	double area;
};


}/* namespace vision */
} /* namespace aanpr */
#endif /* OBJECT2D_H_ */

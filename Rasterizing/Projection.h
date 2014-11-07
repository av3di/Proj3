#ifndef _PROJECTION_H_
#define _PROJECTION_H_

#include "Matrix4.h"
#include <GL/glut.h>

class Projection
{
public:
	Matrix4 p;   // projection matrix

public:
	Projection(double aspect, double fov, double near, double far);
	void resetMatrix(double fov, double aspect, double near, double far);
	~Projection();
	Matrix4& getMatrix();

};

#endif


#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Matrix4.h"
#include <GL/glut.h>

class Viewport
{
public:
	Matrix4 d;   // viewport matrix

public:
	Viewport(double x, double width, double y, double height);
	void resetMatrix(double x, double width, double y, double height);
	~Viewport();
	Matrix4& getMatrix();

};

#endif

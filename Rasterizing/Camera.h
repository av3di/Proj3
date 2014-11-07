#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix4.h"
#include <GL/glut.h>

class Camera
{
public:
	Vector3 e;    // Center of projection
	Vector3 d;    // look at point
	Vector3 up;   // up vector
	Matrix4 c;   // camera matrix

public:
	Camera();
	~Camera();
	Matrix4& getMatrix();
	void constructMatrix();
	void sete(double, double, double);
	void setd(double, double, double);
	void setup(double, double, double);
	void Camera::inverse();

};

#endif

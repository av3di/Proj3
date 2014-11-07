#ifndef _MODEL_H_
#define _MODEL_H_

#include "Matrix4.h"


class Model
{
protected:
	Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
	double angle;                   // rotation angle [degrees]
	bool counter;
public:

	Model();                // Constructor
	Model::~Model();         // Destructor
	Matrix4& getMatrix();
	virtual void draw();
	void spin(double);      // spin cube [degrees]
	void changeCounter();
	void rotateY(double a);
	void translate(double, double, double);
	void scale(double, double, double);
	void rotate(double);
	void reset();
};

#endif


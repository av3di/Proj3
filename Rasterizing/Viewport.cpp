#include "Viewport.h"


Viewport::Viewport(double x, double width, double y, double height)
{
	d.setRow(0, (width-x) / 2.0, 0, 0, (x + width)/2.0);
	d.setRow(1, 0, (height - y)/2.0, 0, (y + height)/2.0);
	d.setRow(2, 0, 0, 1.0/2.0, 1.0/2.0);
	d.setRow(3, 0, 0, 0, 1);
}


Viewport::~Viewport()
{
}

Matrix4& Viewport::getMatrix()
{
	return d;
}
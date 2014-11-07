#include "Projection.h"


Projection::Projection(double fov, double aspect, double near, double far)
{
	p.setRow(0, 1 / (aspect*tan(fov*M_PI / 180.0 / 2.0)), 0, 0, 0);
	p.setRow(1, 0, 1 / (tan((fov*M_PI/180.0) / 2.0)), 0, 0);
	p.setRow(2, 0, 0, (near + far) / (near - far), (2.0 * near*far) / (near - far));
	p.setRow(3, 0, 0, -1, 0);
}

void Projection::resetMatrix(double fov, double aspect, double near, double far)
{
	p.setRow(0, 1 / (aspect*tan(fov*M_PI / 180.0 / 2.0)), 0, 0, 0);
	p.setRow(1, 0, 1 / (tan((fov*M_PI / 180.0) / 2.0)), 0, 0);
	p.setRow(2, 0, 0, (near + far) / (near - far), (2.0 * near*far) / (near - far));
	p.setRow(3, 0, 0, -1, 0);
}

Projection::~Projection()
{
}

Matrix4& Projection::getMatrix()
{
	return p;
}
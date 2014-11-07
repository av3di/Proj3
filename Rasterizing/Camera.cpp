#include "Camera.h"


Camera::Camera() : e(0, 0, 0), d(0, 0, 0), up(0, 0, 0), c()
{
}


Camera::~Camera()
{
}

Matrix4& Camera::getMatrix()
{
	return c;
}

void Camera::constructMatrix()
{
	Vector3 zaxis;
	Vector3 xaxis;
	Vector3 yaxis;

	// Find z-axis
	zaxis = (e - d);
	zaxis.normalize();
	c.setCol(2, zaxis.getX(), zaxis.getY(), zaxis.getZ(), 0);

	// Find x-axis
	xaxis = up.cross(zaxis);
	xaxis.normalize();
	c.setCol(0, xaxis.getX(), xaxis.getY(), xaxis.getZ(), 0);

	// Find y-axis

	yaxis = zaxis.cross(xaxis);
	c.setCol(1, yaxis.getX(), yaxis.getY(), yaxis.getZ(), 0);

	//Set last column
	c.setCol(3, e.getX(), e.getY(), e.getZ(), 1);
}

void Camera::sete(double x, double y, double z)
{
	Vector3 *a = new Vector3(x, y, z);
	e = *a;
}
void Camera::setd(double x, double y, double z)
{
	Vector3 *a = new Vector3(x, y, z);
	d = *a;
}
void Camera::setup(double x, double y, double z)
{
	Vector3 *a = new Vector3(x, y, z);
	up = *a;
}

void Camera::inverse()
{
	Matrix4 t;
	Matrix4 r;

	//Create T matrix
	double x = c.get(0, 3);
	double y = c.get(1, 3);
	double z = c.get(2, 3);
	t.makeTranslate(x, y, z);

	// Create T-1 matrix
	t.set(0, 3, (-1 * t.get(0, 3)));
	t.set(1, 3, (-1 * t.get(1, 3)));
	t.set(2, 3, (-1 * t.get(2, 3)));

	// Create R matrix
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			r.set(row, col, c.get(row, col));
		}
	}
	r.set(0, 3, 0);
	r.set(1, 3, 0);
	r.set(2, 3, 0);
	//r->set(3, 3, 0);

	// Create R-1 matrix
	r.transpose();

	Matrix4 res = r * t;

	// Set camera matrix to its inverse
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			c.set(row, col, res.get(row, col));
		}
	}
	// c.transpose();
}
#include "Dragon.h"

#include <GL/glut.h>

using namespace std;

Dragon::Dragon()
{
	xyzrows = 100250;
}


Dragon::~Dragon()
{
}

void Dragon::draw()
{
	Vector3 normal;
	glBegin(GL_POINTS);
	int count = 0;
	for (int row = 0; row < xyzrows; row++)
	{
		normal.setX(v_xyz[count + 3]);
		normal.setY(v_xyz[count + 4]);
		normal.setZ(v_xyz[count + 5]);
		normal.normalize();
		glNormal3d(normal.getX(), normal.getY(), normal.getZ());
		glVertex3d(v_xyz[count], v_xyz[count + 1], v_xyz[count + 2]);
		count = count + 6;
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}
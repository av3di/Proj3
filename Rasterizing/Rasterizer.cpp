#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Viewport.h"
#include "Projection.h"
#include "Camera.h"
#include "Bunny.h"
#include "Dragon.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "House.h"

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static Viewport vp(0, window_width, 0, window_height);
static Projection projection(60, double(window_width) / (double)window_height, 1.0, 1000.0);
static Camera cam;
static Bunny hop;
static House h;

using namespace std;

struct Color    // generic color class
{
	float r, g, b;  // red, green, blue
};

void loadData()
{
	// point cloud parser goes here
}

// Clear frame buffer
void clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
	}
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{
	int offset = y*window_width * 3 + x * 3;
	pixels[offset] = r;
	pixels[offset + 1] = g;
	pixels[offset + 2] = b;
}

void rasterizeVertex(float x, float y, float z, Matrix4 &multm)
{
	Vector4 point(x, y, z, 1);
	//printf("x: %f, y: %f", x, y);
	//multm.print("Multiplication Matrix:");
	//point.print("OG point");
	Vector4 newp = multm * point;
	//newp.print("New point:");
	newp.dehomogenize();
	if (newp.getX() <= 1 && newp.getX() >= -1 && newp.getY() <= 1 && newp.getY() >= -1 && newp.getZ() <= 1 && newp.getZ() >= -1)
	{
		// Multiply by vp
		newp = vp.getMatrix() * newp;
		drawPoint(newp.getX(), newp.getY(), 1, 1, 1);
	}
	//printf("newpx: %f, newp.y: %f", newp.getX(), newp.getY());

}

void rasterize()
{
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	
	//cam.getMatrix().print("Camera Inverse:");
	//vp.getMatrix().print("Viewport Matrix:");
	//projection.getMatrix().print("Projection Matrix:");
	//hop.getMatrix().print("Bunny Matrix");


	Matrix4 hopcamproj = projection.getMatrix() * cam.getMatrix();
	//hopcamproj.print("proj * cam");

	Matrix4 newM = projection.getMatrix() * cam.getMatrix() * hop.getMatrix();
	//newM.print("Multiplication Mat: ");

	Vector3 normal;
	int count = 0;
	int input = 0;
	for (int row = 0; row < hop.xyzrows; row++)
	{
		Vector4 pt(hop.v_xyz[count], hop.v_xyz[count + 1], hop.v_xyz[count + 2], 1);
		//pt.print("Point is: ");
		//cam.getMatrix().print("Camera Matrix is: (ALL ZEROES)");
		//(cam.getMatrix() * pt).print("Camera * pt");

		//(projection.getMatrix() *  cam.getMatrix() * pt).print("projection * Camera * pt");

		normal.setX(hop.v_xyz[count + 3]);
		normal.setY(hop.v_xyz[count + 4]);
		normal.setZ(hop.v_xyz[count + 5]);
		normal.normalize();
		
		//glNormal3d(normal.getX(), normal.getY(), normal.getZ());
		//glVertex3d(hop.v_xyz[count], hop.v_xyz[count + 1], hop.v_xyz[count + 2]);
		rasterizeVertex(hop.v_xyz[count], hop.v_xyz[count + 1], hop.v_xyz[count + 2], newM);
		//std::cin >> input;
		count = count + 6;
	}

	/* House Draw */
	/*
	int len = 60;
	int index = -1;
	float x;
	float y;
	float z;

	for (int i = 0; i < len; i++)
	{
		index = 3 * h.indices[i];
		x = h.vertices[index];
		y = h.vertices[index + 1];
		z = h.vertices[index + 2];
		rasterizeVertex(x, y, z, newM);
	}
	*/

}

void displayCallback()
{
	clearBuffer();
	rasterize();

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	glutSwapBuffers();
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
{
	cerr << "Key pressed: " << key << endl;
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	h.getMatrix().identity();
	cam.sete(0, 0, 20);
	cam.setd(0, 0, 0);
	cam.setup(0, 1, 0);
	cam.constructMatrix();
	//Matrix4 movecam;
	//movecam.makeTranslate(0, 0, 20); // move back 20

	cam.inverse();

	//hop.getMatrix().identity();
	hop.parseFile("bunny.xyz");
	hop.moveToOrigin();
	hop.fitToWindow();
	hop.getMatrix().print("Bunny Matrix");

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rasterizer");

	loadData();

	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);

	//cam.inverse();
	glutMainLoop();
}

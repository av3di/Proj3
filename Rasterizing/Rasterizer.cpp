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
static Dragon draco;
static int fkey = 1;

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
	Vector4 newp = multm * point;
	newp.dehomogenize();
	if (newp.getX() <= 1 && newp.getX() >= -1 && newp.getY() <= 1 && newp.getY() >= -1 && newp.getZ() <= 1 && newp.getZ() >= -1)
	{
		// Multiply by vp
		newp = vp.getMatrix() * newp;
		drawPoint(newp.getX(), newp.getY(), 1, 1, 1);
	}

}

void rasterize()
{
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	Vector3 normal;
	int count = 0;
	Matrix4 newM;
	projection.resetMatrix(60, double(window_width) / (double)window_height, 1.0, 1000.0);
	vp.resetMatrix(0, window_width, 0, window_height);
	if (fkey == 1)
	{
		newM = projection.getMatrix() * cam.getMatrix() * hop.getMatrix();
		for (int row = 0; row < hop.xyzrows; row++)
		{
			Vector4 pt(hop.v_xyz[count], hop.v_xyz[count + 1], hop.v_xyz[count + 2], 1);

			normal.setX(hop.v_xyz[count + 3]);
			normal.setY(hop.v_xyz[count + 4]);
			normal.setZ(hop.v_xyz[count + 5]);
			normal.normalize();
			rasterizeVertex(hop.v_xyz[count], hop.v_xyz[count + 1], hop.v_xyz[count + 2], newM);
			count = count + 6;
		}
	}
	else if (fkey == 2)
	{
		newM = projection.getMatrix() * cam.getMatrix() * draco.getMatrix();
		for (int row = 0; row < draco.xyzrows; row++)
		{
			normal.setX(draco.v_xyz[count + 3]);
			normal.setY(draco.v_xyz[count + 4]);
			normal.setZ(draco.v_xyz[count + 5]);
			normal.normalize();
			rasterizeVertex(draco.v_xyz[count], draco.v_xyz[count + 1], draco.v_xyz[count + 2], newM);
			count = count + 6;
		}
	}
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

void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_F1:
		fkey = 1;
		displayCallback();
		break;
	case GLUT_KEY_F2:
		fkey = 2;
		displayCallback();
		break;
	}
}

void keyboardCallback(unsigned char key, int, int)
{
	//cerr << "Key pressed: " << key << endl;
	Model *currentM = &hop;
	if (fkey == 1)
		currentM = &hop;
	else if (fkey == 2)
		currentM = &draco;
	switch (key){
	case 27:
		exit(0);
		break;
	case 't':
		currentM->changeCounter();
		break;
	case 'x':
		currentM->translate(-1.0, 0.0, 0.0);
		displayCallback();
		break;
	case 'X':
		currentM->translate(1.0, 0.0, 0.0);
		displayCallback();
		break;
	case 'Z':
		currentM->translate(0.0, 0.0, 1.0);
		displayCallback();
		break;
	case 'z':
		currentM->translate(0.0, 0.0, -1.0);
		displayCallback();
		break;
	case 'y':
		currentM->translate(0.0, -1.0, 0.0);
		displayCallback();
		break;
	case 'Y':
		currentM->translate(0.0, 1.0, 0.0);
		displayCallback();
		break;
	case 's':
		currentM->scale(0.5, 0.5, 0.5);
		displayCallback();
		break;
	case'S':
		currentM->scale(1.5, 1.5, 1.5);
		displayCallback();
		break;
	case 'o':
		currentM->rotate(10);
		displayCallback();
		break;
	case 'O':
		currentM->rotate(-10);
		displayCallback();
		break;
	case 'r':
		currentM->getMatrix().makeRotateY(1.0);
		displayCallback();
		//currentM->reset();
		break;
	}
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//h.getMatrix().identity();
	cam.sete(0, 0, 20);
	cam.setd(0, 0, 0);
	cam.setup(0, 1, 0);
	cam.constructMatrix();

	cam.inverse();

	hop.parseFile("bunny.xyz");
	hop.moveToOrigin();
	hop.fitToWindow();

	draco.parseFile("dragon.xyz");


	draco.moveToOrigin();
	draco.fitToWindow();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rasterizer");

	loadData();

	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
}

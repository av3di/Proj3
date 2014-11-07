#include "Model.h"
#include "Cube.h"
#include "Matrix4.h"
#include <GL/glut.h>

using namespace std;

Model::Model()
{
	angle = 0.0;
	counter = true;
	model2world.identity();
}


Model::~Model()
{
}

Matrix4& Model::getMatrix()
{
	return model2world;
}

void Model::draw()
{
}

void Model::rotate(double a)
{
	Matrix4 *rotation = new Matrix4();
	rotation->makeRotateZ(a);
	model2world = *rotation * model2world;
}

void Model::rotateY(double a)
{
	Matrix4 *rotation = new Matrix4();
	rotation->makeRotateY(a);
	model2world = *rotation * model2world;
}

void Model::scale(double x, double y, double z)
{
	Matrix4 *scaling = new Matrix4;
	scaling->makeScale(x, y, z);
	this->model2world = *scaling * this->model2world;
}

void Model::translate(double x, double y, double z)
{
	Matrix4 *translation = new Matrix4();
	translation->makeTranslate(x, y, z);
	this->model2world = *translation * this->model2world;
}

void Model::spin(double deg)   // deg is in degrees
{
	Matrix4 testing;
	testing.makeRotateY(counter ? deg : -1 * deg);
	angle += deg;
	if (angle > 360.0 || angle < -360.0) angle = 0.0;
	model2world = model2world * testing; // This creates the matrix to rotate the cube}

}

void Model::changeCounter()
{
	this->counter = !(this->counter);
}

void Model::reset()
{
	/* Get All values from last column and multiply by negative one, pass new values to make translate and multiply*/
	Matrix4 translation;
	double x = (-1) * this->getMatrix().get(0, 3);
	double y = (-1) * this->getMatrix().get(1, 3);
	double z = (-1) * this->getMatrix().get(2, 3);
	translation.makeTranslate(x, y, z);
	this->model2world = translation * this->model2world;
}
#include "Vector4.h"
#include <iostream>
#include <math.h>

Vector4::Vector4(){
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(double x1, double y1, double z1, double w1) : x(x1), y(y1), z(z1), w(w1)
{
}

double Vector4::getX() const 
{
	return x;
}

double Vector4::getY() const 
{
	return y;
}

double Vector4::getZ() const 

{
	return z;
}

double Vector4::getW() const 
{
	return w;
}

void Vector4::setX(double x1) 
{
	this->x = x1;
}

void Vector4::setY(double y1) 
{
	this->y = y1;
}

void Vector4::setZ(double z1) 
{
	this->z = z1;
}

void Vector4::setW(double w1)
{
	this->w = w1;
}

Vector4 Vector4::operator+(const Vector4 &v){
	Vector4 *tmp = new Vector4();
	tmp->setX(this->getX() + v.getX());
	tmp->setY(this->getY() + v.getY());
	tmp->setZ(this->getZ() + v.getZ());
	tmp->setW(this->getW() + v.getW());
	return *tmp;
}

Vector4 Vector4::operator-(const Vector4&v) {
	double rx = this->getX() - v.getX();
	double ry = this->getY() - v.getY();
	double rz = this->getZ() - v.getZ();
	double rw = this->getW() - v.getW();
	return Vector4(rx, ry, rz, rw);
}

void Vector4::dehomogenize()
{
	if (this->getW() != 0) // Avoid divide by 0 error
	{
		double vx = this->getX() / this->getW();
		double vy = this->getY() / this->getW();
		double vz = this->getZ() / this->getW();
		double vw = this->getW() / this->getW();
		this->setX(vx);
		this->setY(vy);
		this->setZ(vz);
		this->setW(vw);
	}
}

void Vector4::print(std::string comment)
{
	std::cout << comment << std::endl;
	std::cout << "( " << this->getX() << ", ";
	std::cout << this->getY() << ", ";
	std::cout << this->getZ() << ", ";
	std::cout << this->getW() << ")" << std::endl;
}
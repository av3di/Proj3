#include "Vector3.h"
#include <iostream>
#include <math.h>

Vector3::Vector3(){
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(double x1, double y1, double z1): x(x1), y(y1), z(z1)
{
}

double Vector3::getX() const {
	return x;
}

double Vector3::getY() const {
	return y;
}
double Vector3::getZ() const {
	return z;
}

void Vector3::setX(double x1){
	this->x = x1;
}

void Vector3::setY(double y1){
	this->y = y1;
}
void Vector3::setZ(double z1){
	this->z = z1;
}

Vector3 Vector3::operator+(const Vector3 &v){
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

void Vector3::negate() 
{
	x *= -1;
	y *= -1;
	z *= -1;
}

void Vector3::scale(double s)
{
	x *= s;
	y *= s;
	z *= s;
}

double Vector3::dot(const Vector3&v1)
{
	return((v1.x + x) + (v1.y + y) + (v1.z + z));
}

Vector3 Vector3::cross(const Vector3&v1)
{
	return Vector3((y*v1.z) - (z*v1.y), (z*v1.x) - (x*v1.z), (x*v1.y) - (y*v1.x));

}

double Vector3::length() const
{
	// |v| = sqrt(vx2 + vy2 + vz2)
	return (sqrt((x*x) + (y*y) + (z*z)));

}

void Vector3::normalize()
{
	double length = this->length();
	this->x = this->x /length;
	this->y = this->y / length;
	this->z = this->z / length;
}

void Vector3::print(std::string comment)
{
	std::cout << comment << std::endl;
	std::cout << "( " << this->getX() << ", ";
	std::cout << this->getY() << ", ";
	std::cout << this->getZ() << ")" << std::endl;
}
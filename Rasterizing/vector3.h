#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <string>

class Vector3
{
public:
	Vector3();
	Vector3(double , double , double ); //constructor with three parameters for the vector coordinates
	Vector3 operator+(const Vector3&); //overload operator '+' for addition
	Vector3 operator-(const Vector3&); //overload operator '-' for subtraction
	void negate(); //negation
	void scale(double s); //scale (multipication with scalar value)
	double dot(const Vector3&); //dot product returns result as a double
	Vector3 cross(const Vector3&); //cross product returns results and puts it in calling vector
	double length() const; //length of the vector
	void normalize(); //normalize the vector (make it so that its length is equal to one)
	void print(std::string comment); //print x,y and z components of the vector after a comment string
	double getX() const;
	double getY() const;
	double getZ() const;
	void setX(double);
	void setY(double);
	void setZ(double);
	//variables
	double x, y, z;
};
#endif // _VECTOR3_H
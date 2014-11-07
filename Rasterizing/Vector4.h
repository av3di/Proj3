#ifndef _VECTOR4_H_
#define _VECTOR4_H_
#include <string>

class Vector4
{
	//private:

	public:
		double x, y, z, w;
		double need[4];
		Vector4();
		Vector4(double, double, double, double); // constructor with four parameters for the vector coordinates
		Vector4 operator+(const Vector4&); // overload operator '+' for addition
		Vector4 operator-(const Vector4&); // overload operator '-' for subtraction
		void dehomogenize(); // dehomogenize the vector(scale it so that its fourth component is equal to one)
		void print(std::string comment); // print x, y, z and w components of the vector after a comment string
		double getX() const;
		double getY() const;
		double getZ() const;
		double getW() const;
		void setX(double);
		void setY(double);
		void setZ(double);
		void setW(double);
};
#endif // _VECTOR4_H
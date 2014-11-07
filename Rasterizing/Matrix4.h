#ifndef _MATRIX4_H_
#define _MATRIX4_H_
#include "Vector4.h"
#include "Vector3.h"
#include <string>
#include <iostream>
#define M_PI 3.14159265358979323846

using namespace std;
class Matrix4
{
  protected:
      // matrix elements; first index is for rows, second for columns (row-major)
	  double m[4][4];
  public:
    Matrix4();     
    Matrix4& operator=(const Matrix4&);
    double* getPointer(); 
    void identity(); 
    void transpose();
    void makeRotateY(double); 
	Matrix4 operator*(const Matrix4&);
	double get(int, int) const;
	void set(int, int, double); 
	void Matrix4::setRow(int row, double val1, double val2, double val3, double val4);
	void setCol(int, double, double, double, double);
	Vector4 operator*(const Vector4&);
	void makeRotateX(double);
	void makeRotateZ(double);
	void makeRotate(double, const Vector3&);
	void makeScale(double, double, double);
	void makeTranslate(double, double, double);
	void print(string);
};

#endif
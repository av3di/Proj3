#include <math.h>
#include "Matrix4.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

Matrix4 Matrix4::operator*(const Matrix4 &m2){
	Matrix4 tmp;
	Matrix4 *first = this;
	double sum = 0;
	for (int c = 0; c < 4; c++){
		for (int d = 0; d < 4; d++){
			for (int k = 0; k < 4; k++){
				sum = sum + first->m[c][k] * m2.m[k][d];
			}
			tmp.m[c][d] = sum;
			sum = 0;
		}
	}
	return tmp;
}

Vector4 Matrix4::operator*(const Vector4& v){
	Vector4 temp;
	temp.need[0] = v.x;
	temp.need[1] = v.y;
	temp.need[2] = v.z;
	temp.need[3] = v.w;
	//printf("Going to multiply %f %f %f %f", v.x, v.y, v.z, v.w);
	//printf(" with:\n");
	//print("camera matrix");
	/*Vector4 result;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
		result.need[i] = (m[i][j] * temp.need[j]);
		}
		}*/

	double v_vals[4] = { v.x, v.y, v.z, v.w };
	double res[4] = { 0, 0, 0, 0 };
	for (int row = 0; row < 4; row++)
	{
		double result = 0;
		for (int i = 0; i < 4; i++)
		{
			result += m[row][i] * v_vals[i];

		}
		res[row] = result;
	}
	//return result;
	return Vector4(res[0], res[1], res[2], res[3]);
}

void Matrix4::makeRotateX(double angle){
	angle /= 180 * M_PI;
	identity();
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
}

void Matrix4::makeRotateZ(double angle){
	angle /= 180 * M_PI;
	identity();
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
}

double Matrix4::get(int row, int col)const{
	return (m[row][col]);
}

void Matrix4::set(int row, int col, double val)
{
	m[row][col] = val;
}

void Matrix4::setRow(int row, double val1, double val2, double val3, double val4)
{
	m[row][0] = val1;
	m[row][1] = val2;
	m[row][2] = val3;
	m[row][3] = val4;
}

void Matrix4::setCol(int col, double val1, double val2, double val3, double val4)
{
	m[0][col] = val1;
	m[1][col] = val2;
	m[2][col] = val3;
	m[3][col] = val4;
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}

void Matrix4::makeRotate(double angle, const Vector3 &axis){
	m[0][0] = 1 + (1 - cos(angle))*(pow(axis.x,2) - 1);
	m[0][1] = -axis.z*sin(angle) + (1 - cos(angle)*axis.x*axis.y);
	m[0][2] = axis.y*sin(angle) + (1 - cos(angle)*axis.x*axis.z);
	m[1][0] = axis.z*sin(angle) + (1 - cos(angle)*axis.y*axis.x);
	m[1][1] = 1 + (1 - cos(angle))*(pow(axis.y, 2) - 1);
	m[1][2] = -axis.x*sin(angle) + (1 - cos(angle)*axis.y*axis.z);
	m[2][0] = -axis.y*sin(angle) + (1 - cos(angle)*axis.z*axis.x);
	m[2][1] = axis.x*sin(angle) + (1 - cos(angle)*axis.z*axis.y);
	m[2][2] = 1 + (1 - cos(angle)*(pow(axis.z, 2) - 1));
}
void Matrix4::makeScale(double sx, double sy, double sz){
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	m[3][3] = 1;
}
// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 *temp = new Matrix4();
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp->m[j][i] = m[i][j];
    }
  }
  for (int row = 0; row<4; row++)
  {
	  for (int col = 0; col<4; ++col)
	  {
		  m[row][col] = temp->m[row][col];
	  }
  }
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}

void Matrix4::makeTranslate(double tx, double ty, double tz){
	identity();
	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;
}

void Matrix4::print(string comment){
	cout << comment<< endl;
	for (int row = 0; row < 4; row++){
		for (int col = 0; col < 4; col++){
			cout << m[row][col] << "\t";
		}
		cout << "\n" << endl;
	}
}
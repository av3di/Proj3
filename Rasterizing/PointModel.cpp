#include "PointModel.h"
#ifndef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
PointModel::PointModel()
{
}


PointModel::~PointModel()
{
}

void PointModel::draw()
{

}

void PointModel::parseFile(const char* filename)
{
	// Create pointer to the xyz file
	FILE * xyzf;
	double d;
	//xyzf = fopen(filename, "r");
	errno_t err = fopen_s(&xyzf, filename, "r");
	if (err)
	{
		printf("Couldn't open %s.\n", filename);
	}
	else 
	{
	    for (int count = 0; count < (xyzrows * 6); count++)
		{
			//fscanf(xyzf, "%lf", &d);
			fscanf_s(xyzf, "%lf", &d, sizeof(d));
			v_xyz.push_back(d);
		}
		/*std::cout << "Vector values" << std::endl;
		for (std::vector<double>::const_iterator i = v_xyz.begin(); i != v_xyz.end(); ++i)
			std::cout << *i << ' ';*/
	}
}
void PointModel::findMinMax()
{
	double xmin = 100, ymin = 100, zmin = 100;
	double xmax = -100, ymax = -100, zmax = -100;
	int row = 0;
	int count = 0;

	for (int row = 0; row < xyzrows; row++)
	{
		//Find min and max x
		if (v_xyz[count] < xmin)
			xmin = v_xyz[count];

		if (v_xyz[count] > xmax)
			xmax = v_xyz[count];

		//Find min and max y
		if (v_xyz[count + 1] < ymin)
			ymin = v_xyz[count + 1];
		if (v_xyz[count + 1] > ymax)
			ymax = v_xyz[count + 1];

		// Find min and max z
		if (v_xyz[count + 2] < zmin)
			zmin = v_xyz[count + 2];
		if (v_xyz[count + 2] > zmax)
			zmax = v_xyz[count + 2];

		count = count + 6;
	}
	v_minmax.push_back(xmin);
	v_minmax.push_back(xmax);
	v_minmax.push_back(ymin);
	v_minmax.push_back(ymax);
	v_minmax.push_back(zmin);
	v_minmax.push_back(zmax);

	cout << "Smallest x value is: " << xmin << endl;
	cout << "Largest x value is: " << v_minmax[1] << endl;

	cout << "Smallest y value is: " << ymin << endl;
	cout << "Largest y value is: " << v_minmax[3] << endl;

	cout << "Smallest z value is: " << zmin << endl;
	cout << "Largest z value is: " << v_minmax[5] << "\n" << endl;
}

void PointModel::moveToOrigin()
{
	findMinMax();
	double midx = (v_minmax[0] + v_minmax[1]) / 2;
	double midy = (v_minmax[2] + v_minmax[3]) / 2;
	double midz = (v_minmax[4] + v_minmax[5]) / 2;

	Matrix4 printTranslate;
	printTranslate.makeTranslate(midx * -1, midy * -1, midz * -1);
	printTranslate.print("Translate matrix is : ");
	cout << endl;

	this->model2world = printTranslate * this->model2world;
}

void PointModel::fitToWindow()
{
	// theta to be passed into tan() must be in radians so convert
	double theta = (60.0 / 2.0) / 180.0 * M_PI;

	// tan(theta) * (camera_distance * 2) / (xmax - xmin)
	double factor = tan(theta) * (abs(20) * 2) / (v_minmax[1] - v_minmax[0]);

	/*cout << "tan(theta)" << tan(theta) << endl;

	cout << "v_minmax[1] is" << v_minmax[1] << endl;
	cout << "v_minmax[2] is" << v_minmax[2] << endl;
	cout << "factor is: " << factor << endl;*/

	Matrix4 printScale;
	printScale.makeScale(factor, factor, factor);
	printScale.print("Scale matrix is: ");
	this->model2world = printScale * this->model2world;
}

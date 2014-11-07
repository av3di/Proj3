#ifndef _POINTMODEL_H_
#define _POINTMODEL_H_
#include "Model.h"
#include <vector>
#include <string>
#include <array>

class PointModel : public Model
{
public:
	std::vector<double> v_xyz; // All xyz coords in the xyz file
	std::vector<double> v_minmax; // the smallest and largest xyz values, respectively
	int xyzrows = 0; // Rows in the xyz file

public:
	PointModel();
	~PointModel();
	virtual void draw();
	void parseFile(const char* filename);
	void findMinMax();
	void moveToOrigin();
	void fitToWindow();
};

#endif

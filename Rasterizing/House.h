#ifndef _HOUSE_H_
#define _HOUSE_H_

#include <stdlib.h>
#include <array>
#include "Model.h"

class House: public Model
{
public:
	int nVerts;
	std::array<float, 126> vertices;
	std::array<float, 126> colors;
	std::array<int, 60> indices;

public:
	House();
	~House();
	virtual void draw();
};

#endif
#ifndef _BUNNY_H_
#define _BUNNY_H_

#include "PointModel.h"


class Bunny : public PointModel
{
public:
	Bunny();
	~Bunny();
	virtual void draw();
};

#endif
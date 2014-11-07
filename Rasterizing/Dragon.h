#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "PointModel.h"


class Dragon : public PointModel
{
public:
	Dragon();
	~Dragon();
	virtual void draw();
};

#endif


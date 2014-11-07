#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include "Model.h"


class Cube : public Model
{
  public:

    Cube();   // Constructor
	virtual void draw();
};

#endif


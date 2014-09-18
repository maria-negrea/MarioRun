#pragma once
#include "Point3D.h"

class ColoredPoint3D: public Point3D
{
protected:
	float u, v;
public:
	ColoredPoint3D(float x, float y, float z, float u, float v);
	~ColoredPoint3D(void);
};

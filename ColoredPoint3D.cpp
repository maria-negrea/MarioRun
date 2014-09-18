#include "ColoredPoint3D.h"

ColoredPoint3D::ColoredPoint3D(float x, float y, float z, float u, float v)
:Point3D(x, y, z)
{
	this->u=u;
	this->v=v;/*
	glTexCoord2f(u, v);*/
}

ColoredPoint3D::~ColoredPoint3D(void)
{
}

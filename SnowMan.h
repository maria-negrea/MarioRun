#pragma once
#include "WorldObject.h"
#include "Foot.h"
#include "Pivot.h"

class SnowMan: public WorldObject
{
protected:
	GLUquadricObj *quadratic;
public:
	SnowMan(void);
	void DrawObject();
	~SnowMan(void);
};

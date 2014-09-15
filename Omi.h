#pragma once
#include "WorldObject.h"

class Omi : public WorldObject
{
	void DrawObject();
	unsigned int light;
public:
	Omi(unsigned int light);
	~Omi();

	void Illuminate();
};

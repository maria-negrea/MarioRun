#pragma once

#include "WorldObject.h"
#include "Textures.h"

class Pipe : public WorldObject
{
public:
	Pipe(void);
	~Pipe(void);
	void DrawObject();
};

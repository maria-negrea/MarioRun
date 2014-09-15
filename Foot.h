#pragma once
#include "WorldObject.h"

class Foot: public WorldObject, public Updatable
{
public:
	Foot(void);
	void Update();
	~Foot(void);
};

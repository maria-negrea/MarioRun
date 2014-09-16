#pragma once
#include "WorldObject.h"
#include "Updatable.h"
#include "Collider.h"

class Body : public WorldObject, public Collider
{
private:
	void DrawObject();
public:
	Body(void);
	~Body(void);
};

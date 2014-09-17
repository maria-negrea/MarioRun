#pragma once

#include "WorldObject.h"
#include <math.h>
#include <vector>
#include "Textures.h"
#include "Updatable.h"

class Coin : public WorldObject, public Updatable
{
public:
	Coin(void);
	~Coin(void);
	void DrawObject();
	void Update();
};

#pragma once

#include "WorldObject.h"
#include <math.h>
#include <vector>
#include "Textures.h"
#include "Updatable.h"
#include "Item.h"
#include "Mario.h"

class Coin : public WorldObject, public Updatable, public Item
{
private:
	Mario *mario;
public:
	Coin(void);
	~Coin(void);
	void DrawObject();
	void Update();
	void Function(Mario *mario);
};

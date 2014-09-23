#pragma once

#include "WorldObject.h"
#include "Textures.h"
#include "Updatable.h"
#include "Item.h"
#include "GlobalScore.h"

class Star : public WorldObject, public Updatable, public Item
{
public:
	Star(void);
	~Star(void);
	void DrawObject();
	void Update();
	void Function(Mario *mario);
};

#pragma once

#include "OnRoadObject.h"
#include <math.h>
#include <vector>
#include "Textures.h"
#include "Updatable.h"
#include "Item.h"
#include "GlobalScore.h"

class Coin : public OnRoadObject, public Updatable, public Item
{
public:
	Coin(void);
	~Coin(void);
	void DrawObject();
	void Update();
	bool Function(Mario *mario);
	float angle;
	bool effect;
};

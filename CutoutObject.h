#pragma once
#include "WorldObject.h"
#include "Cutout.h"

class CutoutObject : virtual public WorldObject, public Cutout
{
public:
	CutoutObject();
	~CutoutObject();

	float GetDepth();
	void DrawCutout();
};
#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "Textures.h"
#include "GlobalScore.h"

class Score : public WorldObject, public Updatable
{
public:
	Score(void);
	~Score(void);
	void DrawObject();
	void Update();
	void UpdateScore(int score);
};

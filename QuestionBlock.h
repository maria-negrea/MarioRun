#pragma once
#include"OnRoadObject.h"
#include"Textures.h"
#include"Mushroom.h"
#include "Road.h"

class QuestionBlock : public OnRoadObject
{
	int textureIndex;
	Road* road;
public:
	QuestionBlock(Road* road, GLfloat width, GLfloat heigh, GLfloat size);
	~QuestionBlock(void);
	void DrawObject();
	void Hit();
	void SetIndex(int newIndex);
};

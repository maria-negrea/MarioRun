#pragma once
#include"Textures.h"
#include"Mushroom.h"
#include "Road.h"

class QuestionBlock : public OnRoadObject
{
	int textureIndex;
	Road* road;
	OnRoadObject* insideObject;
public:
	QuestionBlock(OnRoadObject* insideObject, Road* road, GLfloat width, GLfloat heigh, GLfloat size);
	~QuestionBlock(void);
	void DrawObject();
	void Hit();
	void SetIndex(int newIndex);
};


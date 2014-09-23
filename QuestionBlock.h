#pragma once
#include"Textures.h"
#include"Mushroom.h"

class Road;
class OnRoadObject;

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

#include "Road.h"
#include"OnRoadObject.h"

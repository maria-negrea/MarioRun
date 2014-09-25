#pragma once
#include"OnRoadObject.h"
#include"Textures.h"
#include"SmallBox.h"
#include"Item.h"

class SplitBox : public OnRoadObject, public Item
{
public:
	SplitBox(GLfloat width, GLfloat height, GLfloat length);
	~SplitBox(void);
	void Split();
	void DrawObject();
	bool Function(Mario *mario);
};

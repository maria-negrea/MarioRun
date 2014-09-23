#pragma once
#include"WorldObject.h"
#include"Textures.h"
#include"SmallBox.h"
#include"Item.h"

class SplitBox : public WorldObject, public Item
{
public:
	SplitBox(GLfloat width, GLfloat height, GLfloat length);
	~SplitBox(void);
	void Split();
	void DrawObject();
	void Function(Mario *mario);
};

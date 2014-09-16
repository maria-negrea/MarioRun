#pragma once
#include"WorldObject.h"
#include"Textures.h"
#include"Mushroom.h"
class Box:public WorldObject
{
	GLfloat size;
	int textureIndex;
public:
	Box(GLfloat width, GLfloat heigh, GLfloat size);
	~Box(void);
	void DrawObject();
	void Hit();
	void SetIndex(int newIndex);
};

#pragma once
#include"WorldObject.h"
#include"Textures.h"
#include"Mushroom.h"

class QuestionBlock : public WorldObject
{
	GLfloat size;
	int textureIndex;
public:
	QuestionBlock(GLfloat width, GLfloat heigh, GLfloat size);
	~QuestionBlock(void);
	void DrawObject();
	void Hit();
	void SetIndex(int newIndex);
};

#pragma once
#include "Mesh.h"
#include "Updatable.h"

class Head: public Mesh
{
protected:
	GLfloat bigRadius, smallRadius;
public:
	Head(void);
	/*void DrawObject();*/
	GLfloat GetBigRadius();
	GLfloat GetSmallRadius();
	~Head(void);
};

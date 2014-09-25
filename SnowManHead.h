#pragma once
#include "Mesh.h"

class SnowManHead: public Mesh
{
	GLfloat radius;
	GLUquadricObj *quadratic;
public:
	SnowManHead(GLfloat radius);
	void DrawObject();
	void InitializeSnowManSpikes(char* fileName);
	~SnowManHead(void);
};

#pragma once
#include "Mesh.h"
#include "Updatable.h"

class Foot: public Mesh
{
protected:
	int mainTextureIndex;
public:
	Foot(int mainTextureIndex);
	/*void DrawObject();*/
	~Foot(void);
};

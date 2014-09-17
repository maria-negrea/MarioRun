#pragma once
#include "Mesh.h"
#include "Updatable.h"

class Head: public Mesh
{
public:
	Head(void);
	void DrawObject();
	~Head(void);
};

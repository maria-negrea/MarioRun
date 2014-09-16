#pragma once
#include "Mesh.h"
#include "Updatable.h"

class Head: public Mesh, public Updatable
{
public:
	Head(void);
	void Update();
	void DrawObject();
	~Head(void);
};

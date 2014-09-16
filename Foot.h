#pragma once
#include "Mesh.h"
#include "Updatable.h"

class Foot: public Mesh, public Updatable
{
public:
	Foot(void);
	void DrawObject();
	void Update();
	~Foot(void);
};

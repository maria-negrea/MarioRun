#pragma once
#include "Mesh.h"
#include "Updatable.h"

class Torso: public Mesh, public Updatable
{

public:
	Torso(void);
	void Update();
	/*void DrawObject();*/
	~Torso(void);
};

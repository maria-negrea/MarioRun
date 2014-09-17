#pragma once
#include "Head.h"
#include "Torso.h"
#include "Foot.h"

class Goomba: public WorldObject, public Updatable
{
protected:
	Head* head;
	Torso* torso;
	Foot* leftFoot;
	Foot* rightFoot;
public:
	Goomba(void);
	void DrawObject();
	void Update();
	~Goomba(void);
};

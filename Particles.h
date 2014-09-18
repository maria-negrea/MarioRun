#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "ParticleObject.h"

class Particles : public WorldObject, public Updatable
{
private:
	void DrawObject();
	vector<ParticleObject*> particles;
public:
	Particles(void);
	~Particles(void);
	void Update();
};

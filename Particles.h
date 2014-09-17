#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "ParticleObject.h"

class Particles : public WorldObject
{
private:
	void DrawObject();
public:
	Particles(void);
	~Particles(void);
};

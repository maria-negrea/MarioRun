#pragma once

#include "WorldObject.h"
#include "Updatable.h"

class ParticleObject : public WorldObject, public Updatable
{
private:
	void DrawObject();
	Point3D direction;
public:
	ParticleObject(Point3D emitterPosition);
	~ParticleObject(void);
	void Update();
};

#pragma once

#include "WorldObject.h"
#include "Updatable.h"

class ParticleObject : public WorldObject, public Updatable
{
private:
	void DrawObject();
	Point3D direction, initialScale, finalScale;
	double alpha;
	double life;
	double step;
public:
	double GetLife();
	ParticleObject(Point3D emitterPosition, Point3D initialScale, Point3D finalScale);
	~ParticleObject(void);
	void Update();
};

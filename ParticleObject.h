#pragma once

#include "WorldObject.h"
#include "Updatable.h"

typedef int (*AngleGenerator)();

class ParticleObject : public WorldObject, public Updatable
{
private:
	void DrawObject();
	Point3D direction, initialScale, finalScale;
	double alpha, life, step, angle;
	int speed;
	bool rain;
public:
	double GetLife();
	ParticleObject(Point3D direction, Point3D position, Point3D emitterPosition, Point3D initialScale, Point3D finalScale, bool rain, AngleGenerator angleGen);
	~ParticleObject(void);
	bool operator<(ParticleObject& a);
	void Update();
};

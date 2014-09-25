#pragma once

#include "CutoutObject.h"

typedef float (*AngleGenerator)();
typedef void (*AfterEffect)(Point3D position);

class ParticleObject : public CutoutObject, public Updatable
{
private:
	void DrawObject();
	Point3D direction, initialScale, finalScale;
	double alpha, life, step, angle;
	double speed;
	int textureIndex;
	AfterEffect onDeath;
public:
	double GetLife();
	ParticleObject(Point3D direction, 
			Point3D position, 
			Point3D emitterPosition, 
			Point3D initialScale,
			Point3D finalScale, 
			AngleGenerator angleGen,
			AfterEffect onDeath,
			double speed,
			int textureIndex);
	~ParticleObject(void);
	bool operator<(ParticleObject& a);
	void Update();
};

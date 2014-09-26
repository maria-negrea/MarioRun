#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "ParticleObject.h"

typedef Point3D (*DirectionGenerator)();
typedef Point3D (*TranslationGenerator)();

typedef int (*NumberGenerator)();
typedef void (*AfterEffect)(Point3D position);
typedef float (*SpeedGenerator)();

class Particles : public WorldObject, public Updatable
{
private:
	void DrawObject();
	DirectionGenerator directionGenerator;
	TranslationGenerator translationGenerator;
	NumberGenerator gen;
	Point3D initialScale;
	Point3D finalScale;
	AngleGenerator angleGen;
	AfterEffect effect;
	SpeedGenerator speedGenerator;
	
public:
	int textureIndex;
	Particles(DirectionGenerator directionGenerator, 
			TranslationGenerator translationGenerator, 
			NumberGenerator genm, 
			Point3D initialScale,
			Point3D finalScale,
			AngleGenerator angleGen, 
			AfterEffect ef,
			SpeedGenerator speedGenerator,
			int textureIndex);
	~Particles(void);
	void Update();
};




#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "ParticleObject.h"

typedef Point3D (*DirectionGenerator)();
typedef Point3D (*TranslationGenerator)();

typedef int (*NumberGenerator)();
typedef void (*AfterEffect)(Point3D position);

class Particles : public WorldObject, public Updatable
{
private:
	void DrawObject();
	vector<ParticleObject*> particles;
	DirectionGenerator directionGenerator;
	TranslationGenerator translationGenerator;
	NumberGenerator gen;
	bool rain;
	Point3D scale;
	AngleGenerator angleGen;
	AfterEffect effect;
public:
	Particles(DirectionGenerator directionGenerator, TranslationGenerator translationGenerator, bool rain, NumberGenerator genm, Point3D scale, AngleGenerator angleGen, AfterEffect ef);
	~Particles(void);
	void Update();
};




#pragma once

#include "WorldObject.h"
#include "Updatable.h"
#include "ParticleObject.h"

typedef Point3D (*DirectionGenerator)();
typedef Point3D (*TranslationGenerator)();

class Particles : public WorldObject, public Updatable
{
private:
	void DrawObject();
	vector<ParticleObject*> particles;
	DirectionGenerator directionGenerator;
	TranslationGenerator translationGenerator;
public:
	Particles(DirectionGenerator directionGenerator, TranslationGenerator translationGenerator);
	~Particles(void);
	void Update();
};




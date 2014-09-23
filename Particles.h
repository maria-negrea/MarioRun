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
	static Point3D DefDir2();
	static Point3D DefTran2();
public:
	Particles(DirectionGenerator directionGenerator = DefDir2, TranslationGenerator translationGenerator = DefTran2);
	~Particles(void);
	void Update();
};




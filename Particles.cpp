#include "Particles.h"
#include <time.h>
#include <algorithm>

Particles::Particles(DirectionGenerator directionGenerator, 
					 TranslationGenerator translationGenerator, 
					 NumberGenerator gen, 
					 Point3D initialScale, 
					 Point3D finalScale, 
					 AngleGenerator angleGen, 
					 AfterEffect ef,
					 SpeedGenerator speedGenerator,
					 int textureIndex)
{
	this->directionGenerator = directionGenerator;
	this->translationGenerator = translationGenerator;
	this->speedGenerator = speedGenerator;
	this->gen = gen;
	this->initialScale = initialScale;
	this->finalScale = finalScale;
	this->angleGen = angleGen;
	this->effect = ef;
	this->textureIndex = textureIndex;
}



Particles::~Particles(void)
{
}

void Particles::DrawObject() 
{
}

void Particles::Update() 
{
	for(int i=0; i < gen(); i++) 
	{
		ParticleObject* particle = new ParticleObject(directionGenerator(), translationGenerator(),translate, initialScale, finalScale, angleGen,effect,speedGenerator(),textureIndex);
		scene->AddObject(particle);
	}
}

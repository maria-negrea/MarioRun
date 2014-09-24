#include "Particles.h"
#include <time.h>
#include <algorithm>

Particles::Particles(DirectionGenerator directionGenerator, TranslationGenerator translationGenerator, bool rain, NumberGenerator gen, Point3D scale, AngleGenerator angleGen, AfterEffect ef)
{
	this->directionGenerator = directionGenerator;
	this->translationGenerator = translationGenerator;
	this->rain = rain;
	this->gen = gen;
	this->scale = scale;
	this->angleGen = angleGen;
	this->effect = ef;
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
		ParticleObject* particle = new ParticleObject(directionGenerator(), translationGenerator(),translate, scale, Point3D(0.0, 0.0, 0.0), this->rain, angleGen);
		if(rain == false)
			particle->Rotate(Point3D(180,0,0));
		particles.push_back(particle);

		scene->AddObject(particle);
	}

	for(int i=0; i < particles.size(); i++) 
	{
		particles[i]->Update();
	}
	for(int i=0; i < particles.size(); i++) 
	{
		if(particles[i]->GetLife() > 1.0) 
		{
			this->effect(particles[i]->GetTranslate());
			scene->RemoveObject(particles[i]);
			particles.erase(particles.begin() + i);
		}
	}

	sort(particles.begin(), particles.end());
}

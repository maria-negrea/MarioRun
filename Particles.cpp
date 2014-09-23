#include "Particles.h"
#include <time.h>

Particles::Particles(DirectionGenerator directionGenerator, TranslationGenerator translationGenerator)
{
	this->directionGenerator = directionGenerator;
	this->translationGenerator = translationGenerator;
}

Particles::~Particles(void)
{
}

void Particles::DrawObject() 
{

}

void Particles::Update() {
	
	for(int i=0; i < rand() % 10 + 1; i++) {
		ParticleObject* particle = new ParticleObject(directionGenerator(), translationGenerator(),translate, Point3D(1.0, 1.0, 1.0), Point3D(0.0, 0.0, 0.0));
		//particle->Rotate(Point3D(180,0,0));
		particles.push_back(particle);

		scene->AddObject(particle);
	}

	for(int i=0; i < particles.size(); i++) {
		particles[i]->Update();
	}
	for(int i=0; i < particles.size(); i++) {
		if(particles[i]->GetLife() > 1.0) {
			scene->RemoveObject(particles[i]);
			particles.erase(particles.begin() + i);
		}
	}
}

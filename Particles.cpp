#include "Particles.h"
#include <time.h>
#include <algorithm>


Point3D Particles::DefDir2()
{
	int a = rand() % 100-50, b = rand() % 100-50, c = rand() % 100-50;
	return Point3D(a*1.0, b*1.0, c*1.0).Normalize();
}

Point3D Particles::DefTran2() {
	return Point3D(rand() % 5, rand() % 5, 0.0);
}

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
	
	for(int i=0; i < rand() % 4 + 1; i++) {
		ParticleObject* particle = new ParticleObject(directionGenerator(), translationGenerator(),translate, Point3D(3.0, 3.0, 3.0), Point3D(0.0, 0.0, 0.0));
		particle->Rotate(Point3D(0,0,rand()%360));
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

	sort(particles.begin(), particles.end());
}

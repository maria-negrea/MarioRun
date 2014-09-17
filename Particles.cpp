#include "Particles.h"
#include <time.h>

Particles::Particles(void)
{
	particles.push_back(new ParticleObject(GetTranslate()));
	particles.push_back(new ParticleObject(GetTranslate()));
	particles.push_back(new ParticleObject(GetTranslate()));
	particles.push_back(new ParticleObject(GetTranslate()));
}

Particles::~Particles(void)
{
}

void Particles::DrawObject() {
	if(rand() % 2 == 0)
		particles.push_back(new ParticleObject(GetTranslate()));
	for(int i=0; i < particles.size(); i++) {
		particles[i]->Draw();
	}
	if(particles.size() > 20)
		particles.erase(particles.begin());
}

void Particles::Update() {
	for(int i=0; i < particles.size(); i++) {
		particles[i]->Update();
	}
}

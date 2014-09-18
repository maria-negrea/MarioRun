#include "Particles.h"
#include <time.h>

Particles::Particles(void)
{
}

Particles::~Particles(void)
{
}

void Particles::DrawObject() {
	
	for(int i=0; i < rand() % 5; i++) {
		ParticleObject* particle = new ParticleObject(GetTranslate(), Point3D(5.0, 5.0, 5.0), Point3D(0.0, 0.0, 0.0));
		particle->Rotate(Point3D(0,0,rand()%360));
		particles.push_back(particle);
	}

	/*AddChild(particle);*/
	
	for(int i=0; i < particles.size(); i++) {
		particles[i]->Draw();
	}
	//if(particles.size() > 50) {
	//	/*RemoveChild(children[0]);
	//	children.erase(children.begin());*/
	//	particles.erase(particles.begin());
	//}
}

void Particles::Update() {
	for(int i=0; i < particles.size(); i++) {
		particles[i]->Update();
	}
	for(int i=0; i < particles.size(); i++) {
		if(particles[i]->GetLife() > 1.0) {
			particles.erase(particles.begin() + i);
		}
	}
}

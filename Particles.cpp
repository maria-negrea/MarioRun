#include "Particles.h"
#include <time.h>

Particles::Particles(void)
{
}

Particles::~Particles(void)
{
}

void Particles::DrawObject() {
	
	ParticleObject* particle = new ParticleObject(GetTranslate());
	particle->Rotate(Point3D(0,0,rand()%360));
	AddChild(particle);

	if(children.size() > 10) {
		RemoveChild(children[0]);
	}
}

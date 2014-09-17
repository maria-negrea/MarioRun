#include "ParticleObject.h"
#include <time.h>

ParticleObject::ParticleObject(Point3D emitterPosition)
{
	//srand(time(0));
	Translate(emitterPosition + Point3D(0.0, rand() % 2, 0.0));
	int a = rand() % 100-50, b = rand() % 100-50, c = rand() % 100-50;
	direction = Point3D(a*1.0, b*1.0, c*1.0).Normalize()*50;
	//Rotate(scene->GetCamera().GetForward());
}

ParticleObject::~ParticleObject(void)
{
}

void ParticleObject::DrawObject() {
	glColor3f ( 1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(-1.0, 0.0,  1.0);
		glVertex3f( 1.0, 0.0,  1.0);
		glVertex3f( 1.0, 1.0, -1.0);
		glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
	glColor4f ( 1.0, 1.0, 1.0, 1.0);
}

//int count = 0;

void ParticleObject::Update() {
	Translate(direction / 200);
}
#include "ParticleObject.h"
#include <time.h>
#include "Textures.h"

ParticleObject::ParticleObject(Point3D emitterPosition)
{
	//srand(time(0));
	//Translate(emitterPosition + Point3D(0.0, rand() % 2, 0.0));
	int a = rand() % 100-50, b = rand() % 100-50, c = rand() % 100-50;
	direction = Point3D(a*1.0, b*1.0, c*1.0).Normalize()*50;
	alpha = rand() % 10 / 10 + 1.6;
}

ParticleObject::~ParticleObject(void)
{
}

void ParticleObject::DrawObject() {
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[4]);
	glColor4f ( 1.0, 1.0, 1.0, alpha);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);glVertex3f(-1.5, 1.5,  0.0);
		glTexCoord2f(1, 0);glVertex3f( 1.5, 1.5,  0.0);
		glTexCoord2f(1, 1);glVertex3f( 1.5, -1.5, 0.0);
		glTexCoord2f(0, 1);glVertex3f(-1.5, -1.5, 0.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f ( 1.0, 1.0, 1.0, 1.0);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

//int count = 0;

void ParticleObject::Update() {
	Translate(direction / 100);
	
	if(scene != NULL)
	{
		rotate.y = -parent->GetRotate().y+scene->GetCamera()->GetRotate().y;
		rotate.x = -parent->GetRotate().x+scene->GetCamera()->GetRotate().x;
	}
}
#include "ParticleObject.h"
#include <time.h>
#include "Textures.h"



ParticleObject::ParticleObject(Point3D direction,Point3D position, Point3D emitterPosition, Point3D initialScale, Point3D finalScale)
{
	Translate(emitterPosition+position);
	this->direction = direction;
	alpha = rand() % 10 / 10 + 0.6;
	
	this->step = (rand()%10) / 100.0 + 0.01;
	life = 0.0;

	this->initialScale = initialScale;
	this->finalScale = finalScale;

	this->angle = rand() % 100 + 10;
	
	this->speed = ((rand()%50)+30) / 40;
}

ParticleObject::~ParticleObject(void)
{

}


bool ParticleObject::operator<(ParticleObject& a)
{
	Point3D camera = scene->GetCamera()->GetTranslate();
	return (this->GetTranslate()-camera).Magnitude() < (a.translate-camera).Magnitude();
}

void ParticleObject::DrawObject() {
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);
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
	//glEnable(GL_DEPTH_TEST);
}

void ParticleObject::Update() {
	life += step;
	float currentSpeed = speed + (0.0 - speed)*life;
	Translate(direction*currentSpeed);
	
	if(scene != NULL)
	{
		rotate.y = scene->GetCamera()->GetRotate().y;
		rotate.x = scene->GetCamera()->GetRotate().x;
	}

	scale.x = initialScale.x + (finalScale.x - initialScale.x)*life;
	scale.y = initialScale.y + (finalScale.y - initialScale.y)*life;
	scale.z = initialScale.z + (finalScale.z - initialScale.z)*life;
	rotate.z = 0.0 + (angle - 0.0)*life;
}

double ParticleObject::GetLife() {
	return life;
}
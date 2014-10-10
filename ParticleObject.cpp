#include "ParticleObject.h"
#include <time.h>
#include "Textures.h"



ParticleObject::ParticleObject(Point3D direction,Point3D position, Point3D emitterPosition, Point3D initialScale, Point3D finalScale, AngleGenerator angleGen,AfterEffect onDeath, double speed, int textureIndex)
{
	Translate(emitterPosition+position);
	this->direction = direction;
	alpha = rand() % 10 / 10 + 0.6;
	
	this->step = 0.04;
	//this->step = (rand()%10) / 100.0 + 0.1;
	life = 0.0;

	this->initialScale = initialScale;
	this->finalScale = finalScale;
	this->angle = angleGen();
	this->onDeath = onDeath;
	this->textureIndex = textureIndex;

	if(this->angle == 180)
		rotate.z = this->angle;
	
	this->speed = speed;

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
	
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.5f);

	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[textureIndex]);
	/*glColor4f ( 1.0, 1.0, 1.0, 1.0);*/
	glBegin(GL_QUADS);
		glTexCoord2f(0.3, 0.3);glVertex3f(-1.5, 1.5,  0.0);
		glTexCoord2f(0.3, 0.6);glVertex3f( 1.5, 1.5,  0.0);
		glTexCoord2f(0.6, 0.6);glVertex3f( 1.5, -1.5, 0.0);
		glTexCoord2f(0.6, 0.3);glVertex3f(-1.5, -1.5, 0.0);
	glEnd();
	/*glColor4f ( 1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
}

void ParticleObject::Update() 
{
	life += step;
	if(life > 1.0)
	{
		scene->RemoveObject(this);
		if(onDeath != NULL)
		{
			onDeath(Point3D(translate.x,0.1,translate.z));
		}
	}
	else
	{
		//float currentSpeed = speed + (0.0 - speed)*life;
		Translate(direction*speed);
		
		if(scene != NULL)
		{
			rotate.y = scene->GetCamera()->GetRotate().y;
			rotate.x = scene->GetCamera()->GetRotate().x;
		}

		scale = initialScale + (finalScale - initialScale)*life;
		if(this->angle != 180)
			rotate.z = 0.0 + (angle - 0.0)*life;
	}
}
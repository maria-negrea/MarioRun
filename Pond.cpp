#include "Pond.h"
#include "Textures.h"


Pond::Pond(Scene *scene)
{
	this->scene = scene;
}

Pond::~Pond()
{
}

void Pond::DrawObject() {
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glColor4f ( 1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[15]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);glVertex3f(-1.5, 0.01, 1.5);
		glTexCoord2f(1, 0);glVertex3f( 1.5, 0.01, 1.5);
		glTexCoord2f(1, 1);glVertex3f( 1.5, 0.01, -1.5);
		glTexCoord2f(0, 1);glVertex3f(-1.5, 0.01, -1.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f ( 1.0, 1.0, 1.0, 1.0);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void Pond::Update() {
	
}
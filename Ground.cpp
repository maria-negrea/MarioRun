#include "Ground.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(0.0,0.5,0.5);
	glBegin(GL_QUADS);
		glTexCoord2f(1, 1); glVertex3f( 10000,0,10000);
		glTexCoord2f(0, 1); glVertex3f( 10000,0,-10000);
		glTexCoord2f(0, 0); glVertex3f( -10000,0,-10000);
		glTexCoord2f(1, 0); glVertex3f( -10000,0,10000);
	glEnd();
}
#include "Ground.h"

Ground::Ground()
{
	height = 0.1;
	width = 20000;
	length = 20000;

	Translate(Point3D(0,-0.1,0));
}

Ground::~Ground()
{
}

void Ground::DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(0.0,0.5,0.5);
	glBegin(GL_QUADS);
		glTexCoord2f(1, 1); glVertex3f( 10000,0.0,10000);
		glTexCoord2f(0, 1); glVertex3f( 10000,0.0,-10000);
		glTexCoord2f(0, 0); glVertex3f( -10000,0.0,-10000);
		glTexCoord2f(1, 0); glVertex3f( -10000,0.0,10000);
	glEnd();
	glColor4f(1,1,1,1);
}
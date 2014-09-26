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
	if(this->isSummer)
	{
		glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[25]);
	}

	if(this->isWinter)
	{
		glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[27]);
	}
	
	glBegin(GL_QUADS);
		glTexCoord2f(1000, 1000); glVertex3f( 10000,0.0,10000);
		glTexCoord2f(0, 1000); glVertex3f( 10000,0.0,-10000);
		glTexCoord2f(0, 0); glVertex3f( -10000,0.0,-10000);
		glTexCoord2f(1000, 0); glVertex3f( -10000,0.0,10000);
	glEnd();
}
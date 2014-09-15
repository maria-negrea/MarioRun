#include "Mario.h"

Mario::Mario()
{
}

Mario::~Mario()
{

}

void DrawHead()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( 0, 1.0, 0);
		glTexCoord2f(0, 0); glVertex3f( 0, 1.0, 0);
	glEnd();
}

void Mario::DrawObject()
{

	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[2]);
	DrawHead();
}
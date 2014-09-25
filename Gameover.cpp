#include "Gameover.h"
#include"Textures.h"
Gameover::Gameover(GLfloat width, GLfloat height, GLfloat length)
{
	this->width=width;
	this->height=height;
	this->length=length;
}

Gameover::~Gameover(void)
{
}
void Gameover::DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[22]);
	glBegin(GL_QUADS);
		  glTexCoord2f(0, 1); glVertex3f(0-width/2., 0,-length);
		  glTexCoord2f(1, 1); glVertex3f(width/2,0 ,-length);
		  glTexCoord2f(1, 0); glVertex3f(width/2,height/2.,-length);
		  glTexCoord2f(0, 0); glVertex3f(0-width/2.,height/2. ,-length);
    glEnd();
}

void Gameover::Update()
{
 	this->translate = scene->GetCamera()->GetTranslate() + scene->GetCamera()->GetForward() * 4 + Point3D(0, 5, 0) + scene->GetCamera()->GetRight() * 2;
	this->rotate = scene->GetCamera()->GetRotate();
}

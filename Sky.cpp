#include "Sky.h"
#include "Textures.h"

Sky::Sky(GLfloat size)
:size(size)
{
}

Sky::~Sky(void)
{
}

void Sky::DrawObject()
{
    if(WorldObject::isSummer)
	{
		glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[18]);
	}
	if(WorldObject::isWinter)
	{
		glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[31]);
	}
    glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0); glVertex3f(-size, -size,  size);
        glTexCoord2f(0.5, 0.33); glVertex3f( size, -size,  size);
        glTexCoord2f(0.25, 0.33); glVertex3f( size, -size, -size);
        glTexCoord2f(0.25, 0); glVertex3f(-size, -size, -size);

		glTexCoord2f(0.5, 0.33); glVertex3f( size, -size, size);
        glTexCoord2f(0.25, 0.33); glVertex3f( size, -size,  -size);
        glTexCoord2f(0.25, 0.66); glVertex3f( size, size, -size);
        glTexCoord2f(0.5, 0.66); glVertex3f( size, size, size);

		glTexCoord2f(0.25, 0.33); glVertex3f( size, -size, -size);
        glTexCoord2f(-0.0001, 0.33); glVertex3f( -size, -size, -size);
        glTexCoord2f(-0.0001, 0.66); glVertex3f( -size, size, -size);
        glTexCoord2f(0.25, 0.66); glVertex3f( size, size, -size);

		glTexCoord2f(1.01, 0.33); glVertex3f( -size, -size, -size);
        glTexCoord2f(0.75, 0.33); glVertex3f( -size, -size,  size);
        glTexCoord2f(0.75, 0.66); glVertex3f( -size, size, size);
        glTexCoord2f(1.01, 0.66); glVertex3f(-size, size, -size);

		glTexCoord2f(0.75, 0.33); glVertex3f( -size, -size, size);
        glTexCoord2f(0.5, 0.33); glVertex3f( size, -size,  size);
        glTexCoord2f(0.5, 0.66); glVertex3f( size, size, size);
        glTexCoord2f(0.75, 0.66); glVertex3f(-size, size, size);

		glTexCoord2f(0.5, 0.66); glVertex3f(-size, size,  size);
        glTexCoord2f(0.5, 1); glVertex3f( size, size,  size);
        glTexCoord2f(0.25, 1); glVertex3f( size, size, -size);
        glTexCoord2f(0.25, 0.66); glVertex3f(-size, size, -size);
    glEnd();

	//glBegin(GL_QUADS);
	//	//4
	//	glTexCoord2f(0.75, 0.0); glVertex3f( size, -size, size);
 //       glTexCoord2f(0.0, 0.0); glVertex3f( size, -size,  -size);
 //       glTexCoord2f(0.0, 1.0); glVertex3f( size, size, -size);
 //        glTexCoord2f(0.75, 1.0); glVertex3f( size, size, size);

	//	//1
	//	glTexCoord2f(0.0, 0.0); glVertex3f( size, -size, -size);
 //       glTexCoord2f(0.25, 0.0); glVertex3f( -size, -size, -size);
 //       glTexCoord2f(0.25, 1.0); glVertex3f( -size, size, -size);
 //       glTexCoord2f(0.0, 1.0); glVertex3f( size, size, -size);
	//	
	//	//2
	//	glTexCoord2f(0.25, 0.0); glVertex3f( -size, -size, -size);
 //       glTexCoord2f(0.5, 0.0); glVertex3f( -size, -size,  size);
 //       glTexCoord2f(0.5, 1.0); glVertex3f( -size, size, size);
 //       glTexCoord2f(0.25, 1.0); glVertex3f(-size, size, -size);

	//	//3
	//	glTexCoord2f(0.5, 0.0); glVertex3f( -size, -size, size);
 //       glTexCoord2f(0.75, 0.0); glVertex3f( size, -size,  size);
 //       glTexCoord2f(0.75, 1.0); glVertex3f( size, size, size);
 //       glTexCoord2f(0.5, 1.0); glVertex3f(-size, size, size);
 //   glEnd();
}

void Sky::Update()
{
}
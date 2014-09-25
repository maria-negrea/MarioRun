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
    glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[18]);
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
}

void Sky::Update()
{
}
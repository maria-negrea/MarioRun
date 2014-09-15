#include "Box.h"

Box::~Box(void)
{
}

Box::Box(GLfloat sizeX ,GLfloat sizeY ,GLfloat sizeZ )
	:sizeX(sizeX),sizeY(sizeY),sizeZ(sizeZ)
{
}

void Box::DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
		glColor3f(1.0,0.0,0.0);
		glTexCoord2f(1, 1); glVertex3f( sizeX,2*sizeY,sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,2*sizeY,sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(1, 0); glVertex3f( sizeX,2*sizeY,-sizeZ);

		glColor3f(0.0,1.0,0.0);
		glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);

		glColor3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0); glVertex3f( sizeX,2*sizeY,sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,2*sizeY,sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);
		glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);

		glColor3f(1.0,0.0,1.0);
		glTexCoord2f(1, 1); glVertex3f( sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);

		glColor3f(1.0,1.0,0.0);
		glTexCoord2f(0, 1); glVertex3f( sizeX,2*sizeY,sizeZ);
		glTexCoord2f(0, 0); glVertex3f( sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);
		glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);

		glColor3f(0.0,1.0,1.0);
		glTexCoord2f(1, 1); glVertex3f( -sizeX,2*sizeY,sizeZ);
		glTexCoord2f(1, 0); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);
	glEnd();
}

#include "Box.h"

Box::~Box(void)
{
}
Box::Box(GLfloat sizeX ,GLfloat sizeY ,GLfloat sizeZ )
	:sizeX(sizeX),sizeY(sizeY),sizeZ(sizeZ)
{
	length = sizeZ*2;
	width = sizeX*2;
	height = sizeY*2;
}

void Box::DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[3]);
	glBegin(GL_QUADS);
		///*glTexCoord2f(1, 1); glVertex3f( sizeX,2 *sizeY,sizeZ);
		//glTexCoord2f(0, 1); glVertex3f( -sizeX,2*sizeY,sizeZ);
		//glTexCoord2f(0, 0); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		//glTexCoord2f(1, 0); glVertex3f( sizeX,2*sizeY,-sizeZ);

		//glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);
		//glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);
		//glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		//glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);

		//glTexCoord2f(1, 0); glVertex3f( sizeX,2*sizeY,sizeZ);
		//glTexCoord2f(0, 0); glVertex3f( -sizeX,2*sizeY,sizeZ);
		//glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);
		//glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);

		//glTexCoord2f(1, 1); glVertex3f( sizeX,2*sizeY,-sizeZ);
		//glTexCoord2f(0, 1); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		//glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		//glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);

		//glTexCoord2f(0, 1); glVertex3f( sizeX,2*sizeY,sizeZ);
		//glTexCoord2f(0, 0); glVertex3f( sizeX,2*sizeY,-sizeZ);
		//glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);
		//glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);

		//glTexCoord2f(1, 1); glVertex3f( -sizeX,2*sizeY,sizeZ);
		//glTexCoord2f(1, 0); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		//glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		//glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);*/

		glTexCoord2f(1, 0); glVertex3f( sizeX,2 *sizeY,sizeZ);
		glTexCoord2f(1, 1); glVertex3f( -sizeX,2*sizeY,sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(0, 0); glVertex3f( sizeX,2*sizeY,-sizeZ);

		glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);

		glTexCoord2f(0, 0); glVertex3f( -sizeX,0,sizeZ);
		glTexCoord2f(0, 1); glVertex3f( sizeX,0,sizeZ);
		glTexCoord2f(1, 0); glVertex3f( -sizeX,2*sizeY,sizeZ);
		glTexCoord2f(1, 1); glVertex3f( sizeX,2*sizeY,sizeZ);		
		

		glTexCoord2f(1, 1); glVertex3f( sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);

		glTexCoord2f(0, 1); glVertex3f( sizeX,2*sizeY,sizeZ);
		glTexCoord2f(0, 0); glVertex3f( sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(1, 0); glVertex3f( sizeX,0,-sizeZ);
		glTexCoord2f(1, 1); glVertex3f( sizeX,0,sizeZ);

		glTexCoord2f(1, 1); glVertex3f( -sizeX,2*sizeY,sizeZ);
		glTexCoord2f(1, 0); glVertex3f( -sizeX,2*sizeY,-sizeZ);
		glTexCoord2f(0, 0); glVertex3f( -sizeX,0,-sizeZ);
		glTexCoord2f(0, 1); glVertex3f( -sizeX,0,sizeZ);
	glEnd();
}

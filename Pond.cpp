#include "Pond.h"
#include "Textures.h"


Pond::Pond()
{
	rotate.y = rand()%360;
	scale = Point3D(0.2,0.2,0.2);
	life = 0.0;
}

Pond::~Pond()
{
}

void Pond::DrawObject() {
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);*/
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[20]);
	glColor4f ( 1.0, 1.0, 1.0, 1.0);
	glBegin(GL_QUADS);

		/*for(double t=0.0; t<2*PI;t+=0.1)
		{
			glTexCoord2f(, );glVertex3f(sint(t), 0.0, cos(t));

		}*/
		/*glTexCoord2f(0.3, 0.3);glVertex3f(-1.5, 0.0, 1.5);
		glTexCoord2f(0.3, 0.6);glVertex3f( 1.5, 0.0, 1.5);
		glTexCoord2f(0.6, 0.6);glVertex3f( 1.5, 0.0, -1.5);
		glTexCoord2f(0.6, 0.3);glVertex3f(-1.5, 0.0, -1.5);*/

		glTexCoord2f(0, 0);glVertex3f(-1.5, 0.0, 1.5);
		glTexCoord2f(1, 0);glVertex3f( 1.5, 0.0, 1.5);
		glTexCoord2f(1, 1);glVertex3f( 1.5, 0.0, -1.5);
		glTexCoord2f(0, 1);glVertex3f(-1.5, 0.0, -1.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f ( 1.0, 1.0, 1.0, 1.0);
	glDisable(GL_BLEND);
	/*glEnable(GL_DEPTH_TEST);*/
}

void Pond::Update() 
{
	life += 0.01;
	if(life > 1)
		scene->RemoveObject(this);

	Scale(Point3D(0.02,0.02,0.02));
}
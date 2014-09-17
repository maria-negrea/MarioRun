#include "Body.h"

Body::Body(void)
{
	AddPoint(Point3D(-3.0, 0.0,  3.0));
	AddPoint(Point3D( 3.0, 0.0,  3.0));
	AddPoint(Point3D( 3.0, 0.0, -3.0));
	AddPoint(Point3D(-3.0, 0.0, -3.0));

	AddPoint(Point3D(-3.0, 5.0,  3.0));
	AddPoint(Point3D( 3.0, 5.0,  3.0));
	AddPoint(Point3D( 3.0, 5.0, -3.0));
	AddPoint(Point3D(-3.0, 5.0, -3.0));
	length = width = 6.0;
	height = 5.0;
}

Body::~Body(void)
{

}

void drawExterior() {
	glColor3f ( 1.0, 0.0, 1.0);
	glBegin(GL_QUADS); // floor
		glTexCoord2f(0, 0); glVertex3f(-3.0, 0.0,  3.0);
		glTexCoord2f(1, 0); glVertex3f( 3.0, 0.0,  3.0);
		glTexCoord2f(1, 1); glVertex3f( 3.0, 0.0, -3.0);
		glTexCoord2f(0, 1); glVertex3f(-3.0, 0.0, -3.0);
	glEnd();
	glColor3f ( 0.0, 0.0, 1.0);
	glBegin(GL_QUADS); // door
		glTexCoord2f(0, 0);
			glVertex3f(-3.0, 0.0, 3.0);
		glTexCoord2f(0.2, 0);
			glVertex3f(-2.0, 0.0, 3.0);
		glTexCoord2f(0.2, 1);
			glVertex3f(-2.0, 5.0, 3.0);
		glTexCoord2f(0, 1);
			glVertex3f(-3.0, 5.0, 3.0);
	
		glTexCoord2f(0.2, 1);
			glVertex3f(-2.0, 5.0, 3.0);
		glTexCoord2f(0.4, 1);
			glVertex3f(-1.0, 5.0, 3.0);
		glTexCoord2f(0.4, 0.4);
			glVertex3f(-1.0, 2.0, 3.0);
		glTexCoord2f(0.2, 0.4);
			glVertex3f(-2.0, 2.0, 3.0);

		glTexCoord2f(0.4, 0);
			glVertex3f(-1.0, 0.0, 3.0);
		glTexCoord2f(0.6, 0);
			glVertex3f( 0.0, 0.0, 3.0);
		glTexCoord2f(0.6, 1);
			glVertex3f( 0.0, 5.0, 3.0);
		glTexCoord2f(0.4, 1);
			glVertex3f(-1.0, 5.0, 3.0);

		glTexCoord2f(0.6, 0);
			glVertex3f( 0.0, 0.0, 3.0);
		glTexCoord2f(0.9, 0);
			glVertex3f( 2.0, 0.0, 3.0);
		glTexCoord2f(0.9, 0.2);
			glVertex3f( 2.0, 1.0, 3.0);
		glTexCoord2f(0.6, 0.2);
			glVertex3f( 0.0, 1.0, 3.0);
	
		glTexCoord2f(0.6, 0.6);
			glVertex3f( 0.0, 3.0, 3.0);
		glTexCoord2f(0.9, 0.6);
			glVertex3f( 2.0, 3.0, 3.0);
		glTexCoord2f(0.9, 1);
			glVertex3f( 2.0, 5.0, 3.0);
		glTexCoord2f(0.6, 1);
			glVertex3f( 0.0, 5.0, 3.0);

		glTexCoord2f(0.9, 0);
			glVertex3f( 2.0, 0.0, 3.0);
		glTexCoord2f(1, 0);
			glVertex3f( 3.0, 0.0, 3.0);
		glTexCoord2f(1, 1);
			glVertex3f( 3.0, 5.0, 3.0);
		glTexCoord2f(0.9, 1);
			glVertex3f( 2.0, 5.0, 3.0);
	glEnd();
	glColor3f ( 0.0, 1.0, 1.0);
	glBegin(GL_QUADS); // back
		glTexCoord2f(0, 0); glVertex3f(-3.0, 0.0, -3.0);
		glTexCoord2f(1, 0); glVertex3f( 3.0, 0.0, -3.0);
		glTexCoord2f(1, 1); glVertex3f( 3.0, 5.0, -3.0);
		glTexCoord2f(0, 1); glVertex3f(-3.0, 5.0, -3.0);
	glEnd();
	glColor3f ( 1.0, 0.0, 0.0);
	glBegin(GL_QUADS); // left
		glTexCoord2f(0, 0); glVertex3f(-3.0, 0.0, -3.0);
		glTexCoord2f(1, 0); glVertex3f(-3.0, 0.0,  3.0);
		glTexCoord2f(1, 1); glVertex3f(-3.0, 5.0,  3.0);
		glTexCoord2f(0, 1); glVertex3f(-3.0, 5.0, -3.0);
	glEnd();
	glColor3f ( 0.0, 1.0, 0.0);
	glBegin(GL_QUADS); // right
		glTexCoord2f(0, 0); glVertex3f( 3.0, 0.0, -3.0);
		glTexCoord2f(1, 0); glVertex3f( 3.0, 0.0,  3.0);
		glTexCoord2f(1, 1); glVertex3f( 3.0, 5.0,  3.0);
		glTexCoord2f(0, 1); glVertex3f( 3.0, 5.0, -3.0);
	glEnd();
	glColor4f(1, 1, 1, 1);
	glColor3f ( 0.5, 0.5, 0.5);
	glBegin(GL_QUADS); // top
		glTexCoord2f(0, 0); glVertex3f(-3.0, 5.0,  3.0);
		glTexCoord2f(1, 0); glVertex3f( 3.0, 5.0,  3.0);
		glTexCoord2f(1, 1); glVertex3f( 3.0, 5.0, -3.0);
		glTexCoord2f(0, 1); glVertex3f(-3.0, 5.0, -3.0);
	glEnd();
	glColor4f(1, 1, 1, 1);
	
	glColor3f ( 1.0, 1.0, 1.0);
	glBegin(GL_QUADS); 
		glTexCoord2f(0, 0); glVertex3f( 0.0, 1.0,  3.01);
		glTexCoord2f(1, 0); glVertex3f( 2.0, 1.0,  3.01);
		glTexCoord2f(1, 1); glVertex3f( 2.0, 3.0,  3.01);
		glTexCoord2f(0, 1); glVertex3f( 0.0, 3.0,  3.01);
	glEnd();
	glColor4f(1, 1, 1, 1);
}

void Body::DrawObject() {
	//glDisable(GL_LIGHTING);
	drawExterior();
	//glEnable(GL_LIGHTING);	
}

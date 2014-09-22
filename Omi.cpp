#include "Omi.h"

Omi::Omi(unsigned int light)
	:light(light)
{
	glEnable(light);
}

Omi::~Omi(void)
{
} 

void Omi::Illuminate()
{
	ParentPerspective();
	ModifyPerspective();

	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = { 0.0, 10.0, 40.0, -1.0 };

	glLightfv(light,GL_SPECULAR, light_specular);
	glLightfv(light, GL_POSITION, light_position);

	ModifyPerspectiveBack();
	ParentPerspectiveBack();
}

void Omi::DrawObject()
{

}
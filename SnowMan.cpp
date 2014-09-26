#include "SnowMan.h"

SnowMan::SnowMan(void)
{
	quadratic=gluNewQuadric();					
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);

	Foot *leftFoot = new Foot(0.8, 0.5, 0.4, 11);
	Foot *rightFoot = new Foot(0.8, 0.5, 0.4, 11);

	/*Pivot *pivotLeftFoot = new Pivot();
	pivotLeftFoot->AddChild(leftFoot);
	leftFoot->Translate(Point3D(-0.25,-0.5,-0.2));
	leftFoot->Rotate(Point3D(0,110,0));

	Pivot *pivotRightFoot = new Pivot();
	pivotRightFoot->AddChild(rightFoot);
	rightFoot->Translate(Point3D(0.25,-0.5,-0.2));
	rightFoot->Rotate(Point3D(0,70,0));*/

	AddChild(leftFoot);
	AddChild(rightFoot);
	Translate(Point3D(0, 5.0, 0));
}

void SnowMan:: DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[11]);
	
	gluSphere(quadratic,1.3f,100,50);
}

SnowMan::~SnowMan(void)
{
}

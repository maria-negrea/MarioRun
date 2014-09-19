#include "FireBall.h"

FireBall::FireBall(GLfloat radius)
{
	Translate(Point3D(0,5,0));
	width  = 1;
	height = 1;
	length = 1;
	this->radius=radius;
	distanceTravelled = 0;
}

FireBall::~FireBall(void)
{
}
void FireBall::DrawObject()
{   glColor3f(1,1,1);
 
	GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluSphere(quadratic,radius,5,5);
	//gluQuadricTexture(quadratic, GL_TRUE);
}
void FireBall::Update()
{
  Translate(GetForward()*5);

  if(this->distanceTravelled > 5)
	  scene->RemoveObject(this);
  else 
	  distanceTravelled += 0.1;
}

void FireBall::Function(Mario *mario)
{
	scene->RemoveObject(this);
	if(mario->GetBleep() == false && mario->IsBig() == true)
		mario->SetSize();
}
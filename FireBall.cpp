#include "FireBall.h"

Point3D AllDirections()
{
	int a = rand() % 100-50, b = rand() % 100-50, c = rand() % 100-50;
	return Point3D(a*1.0, b*1.0, c*1.0).Normalize();
}
Point3D Planar()
{
	int a = rand() % 100-50, b = rand() % 100-50;
	return Point3D(0.0, 0.0, 0.0).Normalize();
}


FireBall::FireBall(GLfloat radius)
{
	Translate(Point3D(0,5,0));
	width  = 1;
	height = 1;
	length = 1;
	this->radius=radius;
	distanceTravelled = 0;
	particles = NULL;
}

FireBall::~FireBall(void)
{
}
void FireBall::DrawObject()
{
	/*glColor3f(1,1,1);
	GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluSphere(quadratic,radius,5,5);*/
	//gluQuadricTexture(quadratic, GL_TRUE);
}

void FireBall::Update()
{
	if(particles == NULL)
	{
		particles = new Particles(AllDirections, Planar);
		scene->AddObject(particles);
	}
	Translate(GetForward()*5);
	particles->Translate(Point3D(-particles->GetTranslate().x+translate.x, 0.0, -particles->GetTranslate().z+translate.z));
}

void FireBall::Function(Mario *mario)
{
	scene->RemoveObject(this);
	if(mario->GetBleep() == false && mario->IsBig() == true && !mario->GetInvulnerable())
		mario->SetSize();
}
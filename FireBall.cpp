#include "FireBall.h"

Point3D AllDirections()
{
	int a = rand() % 100-50, b = (rand() % 100 - 50) / 200.0, c = rand() % 100-50;
	return Point3D(a*1.0, b*1.0, c*1.0).Normalize();
}
Point3D Planar()
{
	int a = rand() % 100-50, b = rand() % 100-50;
	return Point3D(a*1.0, 0.0, b*1.0).Normalize();
}

Point3D NoDirection()
{
	return Point3D(0.0, 0.0, 0.0).Normalize();
}

Point3D Translation() {
	return Point3D(rand() % 5, rand() % 5, 0.0);
}

Point3D BoxPosition() {
	int a = rand() % 100-50, b = rand() % 100-50, c = rand() % 100 - 50;
	return Point3D(a*1.0, b*1.0, c*1.0).Normalize();
}


Point3D DefaultTranslation() {
	return Point3D(0.0, 0.0, 0.0);
}

int gen() {
	if(rand() % 2 == 0)
		return 1;
	return 0;
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
}

int angleGen() {
	return rand() % 100 + 10;
}

void AfterE(Point3D p) {
}

void FireBall::Update()
{
	if(particles == NULL)
	{
		particles = new Particles(AllDirections, BoxPosition, false, gen, Point3D(3.0, 3.0, 3.0), angleGen, AfterE);
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
#include "FireBall.h"
#include "Particles.h"

Point3D AllDirections()
{
	int a = rand() % 100-50, b = rand() % 100-50, c = rand() % 100-50;
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
	return Point3D(rand() % 10-5, rand() % 10-5, rand() % 10-5).Normalize()*(rand()%10);
}


Point3D DefaultTranslation() {
	return Point3D(0.0, 0.0, 0.0);
}

FireBall::FireBall(GLfloat radius)
{
	Translate(Point3D(0,5,0));
	width  = 1;
	height = 1;
	length = 1;
	this->radius=radius;
	particles = NULL;
	distanceTravelled = 0;
}

FireBall::~FireBall(void)
{
}
void FireBall::DrawObject()
{

}
void FireBall::Update()
{
	if(particles == NULL)
	{
		particles = new Particles(AllDirections, BoxPosition);
		scene->AddObject(particles);
	}
  Translate(GetForward()*5);
  particles->Translate(Point3D(-particles->GetTranslate().x+translate.x, 0.0, -particles->GetTranslate().z+translate.z));
  if(this->distanceTravelled > 5) {
	  scene->RemoveObject(this);
  }
  else 
	  distanceTravelled += 0.1;
}

void FireBall::Function(Mario *mario)
{
	scene->RemoveObject(this);
	if(mario->GetBleep() == false && mario->IsBig() == true)
		mario->SetSize();
}
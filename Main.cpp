#include "Scene.h"
#include "Plant.h"
#include "Box.h"
#include "Mario.h"
#include "MarioCamera.h"
#include "Textures.h"
#include "Goomba.h"
#include "Foot.h"
#include "Torso.h"
#include "Head.h"
#include "Ground.h"
#include "Coin.h"
#include "Particles.h"
#include "QuestionBlock.h"
#include "Input.h"
#include "PlantTulip.h"
#include "PlantHead.h"
#include "PlantLeaf.h"
#include "Road.h"
#include "Omi.h"

Scene *scene;
Camera* mainCamera;
Mario* mario;
Omi* omi;
Particles *particles;
Coin *coin ;
Point3D collision;

int score = 0;

Box *test1, *test2;
QuestionBlock *block;
Road *newRoad = new Road;

PlantHead *newHead=new PlantHead(2,2,2);
PlantLeaf *newLeaf=new PlantLeaf(2,2,2);
PlantTulip *newTulip=new PlantTulip(2,2,2);

vector<Coin*> coins;

//Point3D AllDirections()
//{
//	int a = rand() % 100-50, b = rand() % 100-50, c = rand() % 100-50;
//	return Point3D(a*1.0, b*1.0, c*1.0).Normalize();
//}
//
//Point3D Planar()
//{
//	int a = rand() % 100-50, b = rand() % 100-50;
//	return Point3D(a*1.0, 0.0, b*1.0).Normalize();
//}

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

void AddObjectsToScene() {
	scene->AddObject(newRoad);
	scene->AddObject(test1);
	//scene->AddObject(test2);
	//scene->AddObject(coin);
	
	//scene->AddObject(new Ground);
	//scene->AddObject(particles);
	//scene->AddObject(mario);
	//scene->AddObject(newTulip);
	
	for(int i = 0; i < coins.size(); i++)
		scene->AddObject(coins[i]);
}

void Initialize() 
{
	scene = new Scene();

	//particles = new Particles(Planar, BoxPosition);

	block = new QuestionBlock(7, 7, 7);
	block->Translate(Point3D(0, 12, 70));
	block->AddCollider();
	
	mario = new Mario();
	mario->Translate(Point3D(0,0,0));
	
	double x = 5;

	for(int i = 0; i < 10; i++)
	{
		Coin *newCoin = new Coin;
		newCoin->Translate(newRoad->GetCoinPoint(x, 0, 0));
		newCoin->Scale(Point3D(5.0, 5.0, 5.0));
		newCoin->AddCollider();

		coins.push_back(newCoin);
		x += 2;
	}

	newTulip->AddChild(newHead);
	newTulip->AddChild(newLeaf);
	newHead->Rotate(Point3D(180,0,0));

	newHead->Translate(Point3D(0.4,3.2,0.4));
	newLeaf->Translate(Point3D(0,0,-0.4));
	newTulip->Translate(Point3D(-10,0.5,10));

	newTulip->SetTarget(mario);
	newTulip->Scale(Point3D(1,1,1));

	mainCamera = new MarioCamera(mario);
	mainCamera->Translate(Point3D(0,10,0));
	scene->SetMainCamera(mainCamera);
	
	test1 = new Box(3,3,3);
	test1->Translate(Point3D(5.0, 1.0, 10.0));
	test1->AddCollider();
	/*
	test2 = new Box(2,4,30);
	test2->Translate(Point3D(5.0, 1.0, 120.0));
	test2->AddCollider();*/
	
	//particles->Translate(mario->GetTranslate() + Point3D(0.0, 10.0, 0.0));

	AddObjectsToScene();

	Textures::GetInstance()->LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	Textures::GetInstance()->LoadGLTextures();

	// LIGHTING TEST

	GLfloat light_position[] = { 1.0, 0.0, 1.0};
		
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spec[] = {1, 1, 1, 1};
	GLfloat em[] = {0, 0, 0, 1};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	// /LIGHTING TEST

	glEnable(GL_BLEND);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
}

void Draw()
{
	scene->Render();
}

void Timer(int value)
{
	scene->Update();
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 1000.0);
}



void specialKey(int key, int x, int y)
{ 
	switch(key)
	{
		case GLUT_KEY_LEFT:
			Input::SetLeft(true);
			test1->Rotate(Point3D(0.0, 2.0, 0.0));
			break;
		case GLUT_KEY_RIGHT:
			Input::SetRight(true);
			test1->Rotate(Point3D(0.0, -2.0, 0.0));
			break;
		case GLUT_KEY_F1:
			block->Hit();
			mario->Jump();
			break;
	}
	glutPostRedisplay();
}

void specialUpKey(int key, int x, int y)
{ 
	switch(key)
	{
		case GLUT_KEY_LEFT:
			Input::SetLeft(false);
			break;
		case GLUT_KEY_RIGHT:
			Input::SetRight(false);
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(768, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Mario");
	Initialize();
	glutDisplayFunc(Draw);

	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);

	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
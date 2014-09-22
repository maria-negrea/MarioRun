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
#include "Tree.h"
#include "Input.h"
#include "PlantTulip.h"
#include "PlantHead.h"
#include "PlantLeaf.h"
#include "Road.h"
#include "Line.h"
#include "Segment2D.h"

Scene *scene;
Camera* mainCamera;
Goomba* goomba;
Goomba* goomba2;
Goomba* goomba3;
Mario* mario;

//Box* test1;

Tree* tree;

Omi* omi;
Particles *particles;
Coin *coin ;
Point3D collision;

int score = 0;

Box *test1, *test2;

QuestionBlock *block;
Road *newRoad;
PlantTulip *newTulip;

vector<Coin*> coins;

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

void AddObjectsToScene() 
{
	scene->AddObject(newRoad);

	//scene->AddObject(test1);
	//scene->AddObject(test2);
	//scene->AddObject(coin);
	scene->AddObject(new Ground);
//	scene->AddObject(newTulip);
//	scene->AddObject(particles);
	scene->AddObject(mario);
	scene->AddObject(block);

	newRoad->AddRoadObject(mario);
	newRoad->AddRoadObject(block);

	for(int i = 0; i < coins.size(); i++)
		scene->AddObject(coins[i]);
}

Point3D GetSquareOutside(Point3D pointIn, GLfloat angle)
{
	GLfloat complementAngle=90.0-angle;
	Point3D outside;
	GLfloat l1=pointIn.x*sin(angle*PI/180), l2=pointIn.z*cos(complementAngle*PI/180);
	outside.x=l1+l2;
	outside.z=pointIn.z*sin(complementAngle*PI/180)+pointIn.x*cos(angle*PI/180);
	outside.y=0;

	return outside;
}

void Initialize() 
{
	scene = new Scene();

	newRoad = new Road();

	particles = new Particles(AllDirections, DefaultTranslation);

	block = new QuestionBlock(newRoad,7, 7, 7);
	block->Translate(Point3D(0, 12, 70));
	block->AddCollider();
	
	mario = new Mario();
	mario->Translate(Point3D(0.1,0.0,0.0));
	
	double x = 5;
	for(int i = 0; i < 10; i++)
	{
		Coin *newCoin = new Coin;
		newCoin->Translate(newRoad->GetCoinPoint(x, 0, 0));
		newCoin->Scale(Point3D(5.0, 5.0, 5.0));
		newCoin->AddCollider();

		coins.push_back(newCoin);
		x += 0.1;
	}


	newTulip = new PlantTulip(2,2,2);
	newTulip->Translate(Point3D(-10,0.5,100));

	newTulip->SetTarget(mario);
	newTulip->Scale(Point3D(1,1,1));

	mainCamera = new MarioCamera(mario);
	mainCamera->Translate(Point3D(0,10,0));
	scene->SetMainCamera(mainCamera);

	goomba=new Goomba();
	goomba->SetTarget(mario);
	goomba->Translate(Point3D(-5, 0, 20));
	//tree=new Tree();
	//tree->Translate(Point3D(-5, 0, 40));
	
	test1 = new Box(2,2,10);
	test1->Translate(Point3D(0.0, 1.0, 110.0));
	test1->AddCollider();
	scene->AddObject(test1);
	
	/*particles->Translate(mario->GetTranslate() + Point3D(0.0, 10.0, 0.0));*/

	AddObjectsToScene();

	Textures::GetInstance()->LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);

	Textures::GetInstance()->LoadGLTextures();

	glEnable(GL_DEPTH_TEST);
}

void Draw()
{
	scene->Render();
}

void Timer(int value)
{
	scene->Update();
	particles->Translate(-particles->GetTranslate()+mario->GetTranslate());

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
			break;
		case GLUT_KEY_RIGHT:
			Input::SetRight(true);
			break;
		case GLUT_KEY_F1:
			//block->Hit();
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

	//cout<<GetSquareOutside(Point3D(1, 1, 1), 45).x<<" "<<GetSquareOutside(Point3D(1, 1, 1), 45).y<<" "<<
	//	GetSquareOutside(Point3D(1, 1, 1), 30).z<<endl;

	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);

	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
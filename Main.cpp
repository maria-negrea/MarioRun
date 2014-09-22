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
#include "Omi.h"
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

void AddObjectsToScene() 
{
	scene->AddObject(mario);
	scene->AddObject(newRoad);
	scene->AddObject(test1);
	//scene->AddObject(test2);
	//scene->AddObject(coin);
	scene->AddObject(new Ground);
	scene->AddObject(newTulip);
	//scene->AddObject(particles);
	//scene->AddObject(newTulip);
	//scene->AddObject(block);

	for(int i = 0; i < coins.size(); i++)
		scene->AddObject(coins[i]);

	newRoad->AddRoadObject(mario);
	newRoad->AddRoadObject(block);
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

	particles = new Particles();
	
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
	test1->Translate(Point3D(0.0, 1.0, 10.0));
	test1->AddCollider();

	Textures::GetInstance()->LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	

	// LIGHTING TEST

	GLfloat light_position[] = { 1.0, 1.0, 10.0, 1.0};
		
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat spec[] = {253/255.0, 173/255.0, 0, 1};
	GLfloat spec[] = {1.0, 1.0, 1.0, 1};
	GLfloat em[] = {0, 0, 0, 1};

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	// /LIGHTING TEST

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	Textures::GetInstance()->LoadGLTextures();
	glEnable(GL_BLEND);
	GLfloat mat_amb_diff[] = { 0.1, 0.5, 0.8, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
            mat_amb_diff);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	AddObjectsToScene();
}

void Draw()
{
	scene->Render();
}

void Timer(int value)
{
	scene->Update();
	particles->Translate(-particles->GetTranslate());
	particles->Translate(mario->GetTranslate() + Point3D(0.0, 5.0, 0.0));
	
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
		case GLUT_KEY_F2:
			exit(0);
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

	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);

	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
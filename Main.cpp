#include "Scene.h"
#include"Plant.h"

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

Scene *scene;
Camera* mainCamera;
Mario* mario;
Omi* omi;
Coin *coin ;
Particles *particles = new Particles();
Point3D collision;
int score = 0;
Box *test1, *test2;
QuestionBlock *block;
Road *newRoad = new Road;

void AddObjectsToScene() {
	//scene->AddObject(test1);
	//scene->AddObject(test2);
	//scene->AddObject(coin);
	scene->AddObject(particles);
	//scene->AddObject(new Ground);
	//scene->AddObject(mario);	
	
}

void Initialize() 
{
	scene = new Scene();

	scene->AddObject(newRoad);

	block = new QuestionBlock(4,4,4);
	block->Rotate(Point3D(0,-90,0));
	block->Translate(Point3D(0,5,70));
	
	Omi* omi = new Omi(GL_LIGHT1);
	block->AddChild(omi);
	omi->Translate(Point3D(0,1,0));

	mario = new Mario();
	mario->Translate(Point3D(0,0,30));

	mainCamera = new MarioCamera(mario);
	mainCamera->Translate(Point3D(0,10,0));
	scene->SetMainCamera(mainCamera);
	
	test1 = new Box(2,2,30);
	test1->Translate(Point3D(5.0, 1.0, 90.0));
	test1->AddCollider();
	
	test2 = new Box(2,4,30);
	test2->Translate(Point3D(5.0, 1.0, 120.0));
	test2->AddCollider();
	

	coin = new Coin();
	coin->Translate(mario->GetTranslate() + mario->GetForward()*30 + Point3D(0.0, 6.0, 0.0));
	coin->Scale(Point3D(5.0, 5.0, 5.0));
	
	particles->Translate(mario->GetTranslate() + mario->GetForward()*10);

	AddObjectsToScene();

	Textures::GetInstance()->LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);
	
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	glEnable(GL_LIGHTING);

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
	//vector<Point3D> res = coin->GetBoundingBox();
	//vector<Point3D> res2= mario->GetBoundingBox();

	//collision = res. res2);
	//if(collision != Point3D(0.0, 0.0, 0.0)) {
	//	scene->RemoveObject(coin);
	//	coin = new Coin();
	//	scene->AddObject(coin);
	//	coin->Translate(mario->GetTranslate() + mario->GetForward()*30 + Point3D(0.0, 6.0, 0.0));
	//	coin->Scale(Point3D(5.0, 5.0, 5.0));
	//	score += 10;
	//}
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
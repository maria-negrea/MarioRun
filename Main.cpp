#include "MarioCamera.h"
#include "Environment.h"

#include "GlobalScore.h"
#include "Pond.h"

Scene *scene;
Camera* mainCamera;

Environment* environment;

Omi* omi;
Particles *particles;

Point3D RainDirection()
{
	return Point3D(0.2, -2.0, 0.2).Normalize();
}

Point3D RainTranslation()
{
	int size = 400;
	int a = rand() % size-size/2, b = rand() % size-size/2;
	return Point3D(a, 0.0, b);
}

int RainGenerator() 
{
	return rand() % 20 + 1;
}

float angleG() 
{
	return 180;
}

float ConstantSpeed()
{
	return 4.0;
}

void AfterEff(Point3D p) 
{
	Pond *pond = new Pond();
	pond->Translate(Point3D(p.x, p.y+rand()%100*0.001, p.z));
	environment->AddObject(pond);
}

void Timer(int value)
{
	environment->GetScene()->Update();
	particles->Translate(-particles->GetTranslate());
	particles->Translate(environment->GetMario()->GetTranslate() + Point3D(0.0, 100.0, 0.0));
	glutPostRedisplay();
	
	if(environment->GetMario()->IsDead() == false)
		glutTimerFunc(1, Timer, 0);
}

void Initialize()
{	
	
	bool isDead = false;
	if(environment)
		isDead = environment->GetMario()->IsDead();

	environment=new Environment();
	environment->AddObjectsToScene();
	
	particles = new Particles(RainDirection, RainTranslation, RainGenerator,Point3D(0.2,1,0.2),Point3D(0.2,1,0.2), angleG, AfterEff,ConstantSpeed, 20);//19

	GlobalScore::GetInstance()->SetScore(0);
	WorldObject::isSummer=true;
	WorldObject::isWinter=false;

	if(isDead == true)
		glutTimerFunc(20, Timer, 0);
}

void Draw()
{
	environment->GetScene()->Render();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 1000000.0);
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

void keyPressed(unsigned char key, int x, int y) 
{
	switch(key)
	{
	case (char)13 :
			environment->GetMario()->StartGame();
			break;
	case (char)32 :
			if(environment->GetMario()->GameStatus()
				&& !environment->GetMario()->IsDying()) environment->GetMario()->Jump();
			break;
	case 'r' :
			Initialize();
			break;
	}
}

void InitialState()
{
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	Textures::GetInstance()->LoadGLTextures();

	Initialize();
	glutTimerFunc(20, Timer, 0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(768, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Mario");

	InitialState();
	glutDisplayFunc(Draw);

	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);
	glutKeyboardFunc(keyPressed);

	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
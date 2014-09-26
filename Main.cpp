#include "MarioCamera.h"
#include "Environment.h"
#include "Skin.h"

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
	Pond *pond = new Pond(particles->textureIndex);
	pond->Translate(Point3D(p.x, p.y+rand()%100*0.001, p.z));
	environment->AddObject(pond);
}


Torso* bone1 = new Torso();
Torso* bone2 = new Torso();
Torso* bone3 = new Torso();

void Timer(int value)
{
	environment->GetScene()->Update();
	
	if(particles ==NULL)
	{	
		particles = new Particles(RainDirection, RainTranslation, RainGenerator,Point3D(0.5,1,0.5),Point3D(0.5,1,0.5), angleG, AfterEff,ConstantSpeed, 20);//19	
		environment->AddObject(particles);
	}
	if(WorldObject::isSummer==true)
	{
		particles->textureIndex=20;
		
	}
	if(WorldObject::isWinter==true)
	{
		particles->textureIndex=34;
	}
	
	particles->Translate(-particles->GetTranslate());
	particles->Translate(environment->GetMario()->GetTranslate() + Point3D(0.0, 100.0, 0.0));
	glutPostRedisplay();
	
	if(environment->GetMario()->IsDead() == false)
		glutTimerFunc(20, Timer, 0);
}

void Initialize()
{
	particles=NULL;
	bool isDead = false;
	if(environment)
		isDead = environment->GetMario()->IsDead();

	environment=new Environment();

	environment->AddObjectsToScene();	
	
	GlobalScore::GetInstance()->SetScore(0);
	WorldObject::isSummer=true;
	WorldObject::isWinter=false;

	particles = new Particles(RainDirection, RainTranslation, RainGenerator,Point3D(0.2,1,0.2),Point3D(0.2,1,0.2), angleG, AfterEff,ConstantSpeed, 20);//19

	environment->AddObject(particles);

	//LIGHTING TEST

	//GLfloat light_position[] = { 1.0, 1.0, 10.0, 1.0};
	//	
	//GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	//GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	////GLfloat spec[] = {253/255.0, 173/255.0, 0, 1};
	//GLfloat spec[] = {1.0, 1.0, 1.0, 1};
	//GLfloat em[] = {0, 0, 0, 1};

	////glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	////glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//
	////glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	////glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	////glEnable(GL_LIGHTING);

	//glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);

	//// /LIGHTING TEST

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//
	//glEnable(GL_BLEND);
	//GLfloat mat_amb_diff[] = { 0.1, 0.5, 0.8, 1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
 //           mat_amb_diff);
	//glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	//glEnable ( GL_COLOR_MATERIAL ) ;
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	////glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	////glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, em);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
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
			bone2->Rotate(Point3D(0,0,-4));
			break;
		case GLUT_KEY_RIGHT:
			Input::SetRight(true);
			bone2->Rotate(Point3D(0,0,4));
			break;
		case GLUT_KEY_UP:
			bone1->Rotate(Point3D(0,0,-4));
			break;
		case GLUT_KEY_DOWN:
			bone1->Rotate(Point3D(0,0,4));
			break;
		case GLUT_KEY_F1:
			bone3->Rotate(Point3D(0,0,4));
			break;
		case GLUT_KEY_F2:
			bone3->Rotate(Point3D(0,0,-4));
			break;
		case GLUT_KEY_F3:
			bone2->Rotate(Point3D(4,0,0));
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
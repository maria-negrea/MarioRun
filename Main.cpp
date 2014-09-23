#include "Plant.h"
#include "Box.h"
#include "Textures.h"
#include "Particles.h"
#include "Input.h"
#include "PlantTulip.h"
#include "PlantHead.h"
#include "PlantLeaf.h"
#include "Road.h"
#include "Omi.h"
#include "Line.h"
#include "Segment2D.h"
#include "Environment.h"

Scene *scene;
Camera* mainCamera;
Goomba* goomba;
Mario* mario;

Environment* environment;

Omi* omi;
Particles *particles;
Point3D collision;

int score = 0;

PlantHead *newHead=new PlantHead(2,2,2);
PlantLeaf *newLeaf=new PlantLeaf(2,2,2);
PlantTulip *newTulip=new PlantTulip(2,2,2);


Point3D Dir()
{
	int a = rand() % 100-50, b = (-1)*(rand() % 100 + 50), c = rand() % 100-50;
	return Point3D(0.2, b*1.0, 0.2).Normalize();
}

Point3D Tran()
{
	int a = rand() % 100-50, b = rand() % 100-50;
	return Point3D(a*10.0, 0.0, b*10.0).Normalize()*20;
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
	environment=new Environment();
	environment->AddObjectsToScene();
	
	particles = new Particles(Dir, Tran);

	environment->AddObject(particles);
	
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

	//glEnable(GL_LIGHTING);
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
	environment->GetScene()->Render();
}

void Timer(int value)
{
	environment->GetScene()->Update();
	particles->Translate(-particles->GetTranslate());
	particles->Translate(environment->GetMario()->GetTranslate() + Point3D(0.0, 15.0, 0.0));
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
			environment->GetMario()->Jump();
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
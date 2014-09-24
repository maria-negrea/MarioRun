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
#include "GlobalScore.h"
#include "Pond.h"

Scene *scene;
Camera* mainCamera;
Goomba* goomba;
Mario* mario;

Environment* environment;

Omi* omi;
Particles *particles;
Point3D collision;

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

int generator() {
	return rand() % 10 + 1;
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

int angleG() {
	return 180;
}

void AfterEff(Point3D p) 
{
	Pond *pond = new Pond(environment->GetScene());
	pond->Draw();
	pond->Translate(Point3D(p.x, 0.02, p.z));
	environment->AddObject(pond);
}

void Initialize()
{
	environment=new Environment();
	environment->AddObjectsToScene();
	
	particles = new Particles(Dir, Tran, true, generator, Point3D(0.5, 0.5, 0.5), angleG, AfterEff);

	GlobalScore::GetInstance()->SetScore(0);

	//environment->AddObject(particles);

	// LIGHTING TEST

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
}

void Draw()
{
	environment->GetScene()->Render();
}

void Timer(int value)
{
	environment->GetScene()->Update();
	particles->Translate(-particles->GetTranslate());
	particles->Translate(environment->GetMario()->GetTranslate() + Point3D(0.0, 25.0, 0.0));
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
			Initialize();
			glutDisplayFunc(Draw);
			glutTimerFunc(30, Timer, 0);

			glutSpecialFunc(specialKey);
			glutSpecialUpFunc(specialUpKey);
			break;
	case (char)32 :
			if(environment != NULL) environment->GetMario()->Jump();
			break;

	case 'r' :
			if(environment != NULL) Initialize();
			break;
	}
}  

void DrawTitleScreen()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0, 0, -2);
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[11]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
		glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
		glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
	glEnd();

	glPopMatrix();

	glFlush();
}

void InitializeTitleScreen()
{
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);

	Textures::GetInstance()->LoadGLTextures();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(768, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Mario");

	InitializeTitleScreen();
	glutDisplayFunc(DrawTitleScreen);

	glutKeyboardFunc(keyPressed);

	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
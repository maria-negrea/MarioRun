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

void Initialize()
{
	environment=new Environment();
	environment->AddObjectsToScene();
	
	particles = new Particles(RainDirection, RainTranslation, RainGenerator,Point3D(0.2,1,0.2),Point3D(0.2,1,0.2), angleG, AfterEff,ConstantSpeed, 20);//19

	GlobalScore::GetInstance()->SetScore(0);

	//environment->AddObject(particles);

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
}

void Draw()
{
	environment->GetScene()->Render();
}

void Timer(int value)
{
	environment->GetScene()->Update();
	particles->Translate(-particles->GetTranslate());
	particles->Translate(environment->GetMario()->GetTranslate() + Point3D(0.0, 100.0, 0.0));
	glutPostRedisplay();
	
	if(environment->GetMario()->IsDead() == false)
		glutTimerFunc(30, Timer, 0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 10000.0);
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
			//if(!environment)
			//{
				Initialize();
				glutDisplayFunc(Draw);
				glutTimerFunc(30, Timer, 0);

				glutSpecialFunc(specialKey);
				glutSpecialUpFunc(specialUpKey);
			//}
			break;
	case (char)32 :
			if(environment != NULL) environment->GetMario()->Jump();
			break;

	case 'r' :
			if(environment != NULL) 
			{
				bool isDead = environment->GetMario()->IsDead();
				Initialize();

				if(isDead == true)
					glutTimerFunc(30, Timer, 0);
			}
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
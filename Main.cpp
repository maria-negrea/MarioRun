#include "Scene.h"
#include "Textures.h"
#include "Body.h"

Scene *scene;
Camera* mainCamera;
Body *body = new Body;


void Initialize() 
{
	scene = new Scene();

	mainCamera = new Camera();
	scene->SetMainCamera(mainCamera);
	scene->AddObject(body);
	body->Translate(Point3D(0.0, 0.0, 20.0));
	Textures::GetInstance()->LoadGLTextures();

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
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
// random comm
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
		case GLUT_KEY_RIGHT :
			body->Rotate(Point3D(0.0, 2.0, 0.0));
			break;

		case GLUT_KEY_LEFT :
			body->Rotate(Point3D(0.0, -2.0, 0.0));
			break;

		case GLUT_KEY_DOWN:
			body->Rotate(Point3D(2.0, 0.0, 2.0));
			break;
		case GLUT_KEY_UP:
			body->Rotate(Point3D(-2.0, 0.0, -2.0));
			break;
		
		case GLUT_KEY_PAGE_UP:
			body->Translate(Point3D(0.0, 0.0, 1.0));
			break;

		case GLUT_KEY_PAGE_DOWN:
			body->Translate(Point3D(0.0, 0.0, -1.0));
			break;
		
		case GLUT_KEY_HOME:
			body->Translate(Point3D(1.0, 0.0, 0.0));
			break;
		case GLUT_KEY_END:
			body->Translate(Point3D(-1.0, 0.0, 0.0));
			break;
		/*
		case GLUT_KEY_F1:
			if(door->GetRotate() > Point3D(0.0, -100.0, 0.0))
				door->Rotate(Point3D(0.0, -5.0, 0.0));
			break;
		case GLUT_KEY_F2:
			if(door->GetRotate() < Point3D(0.0, 0.0, 0.0))
				door->Rotate(Point3D(0.0, 5.0, 0.0));
			break;
		*/
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
	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
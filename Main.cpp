#include "Scene.h"
#include "Textures.h"
#include "Goomba.h"
#include "Foot.h"
#include "Torso.h"
#include "Head.h"

Scene *scene;
Camera* mainCamera;
Goomba* goomba;
Foot* foot;
Torso* torso;
Head* head;


void Initialize() 
{
	scene = new Scene();

	mainCamera = new Camera();
	goomba=new Goomba();
	goomba->Translate(Point3D(0,0,10));
	foot=new Foot();
	torso=new Torso();
	head=new Head();
	torso->Translate(Point3D(0,0,10));
	head->Translate(Point3D(0,0,10));
	foot->Translate(Point3D(0,0,9));
	scene->SetMainCamera(mainCamera);
	scene->AddObject(goomba);

	Textures::GetInstance()->LoadGLTextures();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);
	//glEnable(GL_LIGHTING);
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
	case GLUT_KEY_RIGHT :
		goomba->Rotate(Point3D(0,10,0));
		break;
	case GLUT_KEY_LEFT :
		goomba->Rotate(Point3D(0,-10,0));
		break;
	case GLUT_KEY_UP :
		goomba->Rotate(Point3D(10,0,0));
		break;
	case GLUT_KEY_DOWN :
		goomba->Rotate(Point3D(-10,0,0));
		break;

		/*case GLUT_KEY_RIGHT :
		torso->Rotate(Point3D(0,10,0));
		break;
	case GLUT_KEY_LEFT :
		torso->Rotate(Point3D(0,-10,0));
		break;
	case GLUT_KEY_UP :
		torso->Rotate(Point3D(10,0,0));
		break;
	case GLUT_KEY_DOWN :
		torso->Rotate(Point3D(-10,0,0));
		break;*/

	case GLUT_KEY_F1 :
		mainCamera->Translate(Point3D(0.0, 0.0, -1.0));
		break;
	case GLUT_KEY_F2 :
		mainCamera->Translate(Point3D(0.0, 0.0, 1.0));
		break;
	case GLUT_KEY_F3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
		break;
	case GLUT_KEY_F4:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
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
	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}
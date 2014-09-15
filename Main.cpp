#include "Scene.h"
#include "Textures.h"

Scene *scene;
Camera* mainCamera;

void Initialize() 
{
	scene = new Scene();

	mainCamera = new Camera();
	scene->SetMainCamera(mainCamera);
	
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